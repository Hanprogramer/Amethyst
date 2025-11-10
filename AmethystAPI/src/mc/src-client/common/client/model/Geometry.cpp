#include <mc/src-client/common/client/model/Geometry.hpp>
#include <mc/src-client/common/client/renderer/Tessellator.hpp>
#include <mc/src-deps/renderer/MatrixStack.hpp>

Matrix Geometry::Node::getTransform() const 
{
	Matrix mat;

	mat.translate(mPivot);

	mat.rotateXDegrees(mRot.x);
	mat.rotateYDegrees(mRot.y);
	mat.rotateZDegrees(mRot.z);

	mat.scale(mScale);

	mat.translate(mPivot * -1.0f);
	return mat;
}

Matrix Geometry::Box::getTransform() const 
{
	Matrix mat;
	mat.translate(mPivot);

	mat.rotateXDegrees(mRotation.x);
	mat.rotateYDegrees(mRotation.y);
	mat.rotateZDegrees(mRotation.z);

	mat.translate(mPivot * -1.0f);
	return mat;
}

std::array<std::array<char, 4>, 6> boxFaces = {{
    {6, 4, 0, 2}, // down 0, 2, 6, 4
    {5, 7, 3, 1}, // up 1, 5, 7, 3 90deg
    {4, 5, 1, 0}, // north
    {2, 3, 7, 6}, // south
    {6, 7, 5, 4},
    {0, 1, 3, 2}, 
}};

void TessellateBox(const Geometry::Box& box, Tessellator& tess, float texW, float texH, MatrixStack& stack) {
    // Push current transform
    auto ref = stack.push();

    // Apply box pivot + rotation
    ref->translate(box.mPivot);
    ref->rotateXDegrees(box.mRotation.x);
    ref->rotateYDegrees(box.mRotation.y);
    ref->rotateZDegrees(box.mRotation.z);
    ref->translate(box.mPivot * -1.0f);

    // Box corners in local space (no mirroring)
    std::array<Vec3, 8> verts = {
        Vec3(box.mFrom.x, box.mFrom.y, box.mFrom.z),
        Vec3(box.mFrom.x, box.mFrom.y + box.mSize.y, box.mFrom.z),
        Vec3(box.mFrom.x + box.mSize.x, box.mFrom.y, box.mFrom.z),
        Vec3(box.mFrom.x + box.mSize.x, box.mFrom.y + box.mSize.y, box.mFrom.z),
        Vec3(box.mFrom.x, box.mFrom.y, box.mFrom.z + box.mSize.z),
        Vec3(box.mFrom.x, box.mFrom.y + box.mSize.y, box.mFrom.z + box.mSize.z),
        Vec3(box.mFrom.x + box.mSize.x, box.mFrom.y, box.mFrom.z + box.mSize.z),
        Vec3(box.mFrom.x + box.mSize.x, box.mFrom.y + box.mSize.y, box.mFrom.z + box.mSize.z)
    };

    // Tessellate each face
    for (int face = 0; face < 6; face++) {
        const auto& f = boxFaces[face];
        const auto& uv = box.mFaceUVs[face];

        float x1 = uv.mUV.x / texW;
        float x2 = (uv.mUV.x + uv.mUVSize.x) / texW;
        float y1 = uv.mUV.y / texH;
        float y2 = (uv.mUV.y + uv.mUVSize.y) / texH;

        tess.vertexUV(*ref * (verts[f[0]] / Vec3(16.f)), x2, y2);
        tess.vertexUV(*ref * (verts[f[1]] / Vec3(16.f)), x2, y1);
        tess.vertexUV(*ref * (verts[f[2]] / Vec3(16.f)), x1, y1);
        tess.vertexUV(*ref * (verts[f[3]] / Vec3(16.f)), x1, y2);
    }

    stack.pop();
}

void TessellateNode(const Geometry::Node& node, Tessellator& tess, float texW, float texH, MatrixStack& stack) {
    auto ref = stack.push();

    // Apply node pivot / rotation / scale
    ref->translate(node.mPivot);
    ref->rotateXDegrees(node.mRot.x);
    ref->rotateYDegrees(node.mRot.y);
    ref->rotateZDegrees(node.mRot.z);
    ref->scale(node.mScale);
    ref->translate(node.mPivot * -1.0f);

    for (const auto& box : node.mBoxes) {
        TessellateBox(box, tess, texW, texH, stack);
    }

    stack.pop();
}

void Geometry::Tessellate(Tessellator& tess) const
{
	MatrixStack stack;
    stack.push(Matrix()); // identity

    for (const auto& [_, node] : mNodes) {
        TessellateNode(node, tess, mTextureDimensions.x, mTextureDimensions.y, stack);
    }

    stack.pop();
}