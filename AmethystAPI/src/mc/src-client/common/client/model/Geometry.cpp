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
    {4, 0, 2, 6}, // down  (-Y)
    {1, 5, 7, 3}, // up    (+Y)
    {0, 1, 3, 2}, // north (-Z)
    {6, 7, 5, 4}, // south (+Z)
    {4, 5, 1, 0}, // west  (-X)
    {2, 3, 7, 6}  // east  (+X)
}};

inline std::array<Vec2, 4> getRotatedFaceUVs(float x1, float x2, float y1, float y2, QuadUVRotation rot) {
    // bottom-left, top-left, top-right, bottom-right
    std::array<Vec2, 4> uvs = {{
        {x2, y2}, // 0
        {x2, y1}, // 1
        {x1, y1}, // 2
        {x1, y2}  // 3
    }};

    switch (rot) {
        case QuadUVRotation::ZERO:
            break;

        case QuadUVRotation::CW_90_DEG:
            std::rotate(uvs.rbegin(), uvs.rbegin() + 1, uvs.rend());
            break;

        case QuadUVRotation::CW_180_DEG:
            std::rotate(uvs.rbegin(), uvs.rbegin() + 2, uvs.rend());
            break;

        case QuadUVRotation::CW_270_DEG:
            std::rotate(uvs.begin(), uvs.begin() + 1, uvs.end());
            break;

        default:
            break;
    }

    return uvs;
}

void TessellateBox(const Geometry::Box& box, Tessellator& tess, float texW, float texH, MatrixStack& stack) {
    auto ref = stack.push();

    const Vec3 pivotScaled = box.mPivot / Vec3(16.f);

    ref->translate(pivotScaled);
    ref->rotateXRadians(box.mRotation.x);
    ref->rotateYRadians(box.mRotation.y);
    ref->rotateZRadians(box.mRotation.z);
    ref->translate(pivotScaled * -1.0f);

    std::array<Vec3, 8> verts = {
        Vec3(box.mFrom.x, box.mFrom.y, box.mFrom.z),                        // 0
        Vec3(box.mFrom.x, box.mFrom.y + box.mSize.y, box.mFrom.z),          // 1
        Vec3(box.mFrom.x + box.mSize.x, box.mFrom.y, box.mFrom.z),          // 2
        Vec3(box.mFrom.x + box.mSize.x, box.mFrom.y + box.mSize.y, box.mFrom.z),  // 3
        Vec3(box.mFrom.x, box.mFrom.y, box.mFrom.z + box.mSize.z),          // 4
        Vec3(box.mFrom.x, box.mFrom.y + box.mSize.y, box.mFrom.z + box.mSize.z),  // 5
        Vec3(box.mFrom.x + box.mSize.x, box.mFrom.y, box.mFrom.z + box.mSize.z),  // 6
        Vec3(box.mFrom.x + box.mSize.x, box.mFrom.y + box.mSize.y, box.mFrom.z + box.mSize.z)  // 7
    };

    for (int face = 0; face < boxFaces.size(); ++face) {
        const auto& f = boxFaces[face];
        const auto& uv = box.mFaceUVs[face];

        float x1 = uv.mUV.x / texW;
        float x2 = (uv.mUV.x + uv.mUVSize.x) / texW;
        float y1 = uv.mUV.y / texH;
        float y2 = (uv.mUV.y + uv.mUVSize.y) / texH;

        auto faceUVs = getRotatedFaceUVs(x1, x2, y1, y2, uv.mUvRotation);

        Vec3 v0 = *ref * (verts[f[0]] / Vec3(16.f));
        Vec3 v1 = *ref * (verts[f[1]] / Vec3(16.f));
        Vec3 v2 = *ref * (verts[f[2]] / Vec3(16.f));
        Vec3 v3 = *ref * (verts[f[3]] / Vec3(16.f));

        tess.vertexUV(v0, faceUVs[0].x, faceUVs[0].y);
        tess.vertexUV(v1, faceUVs[1].x, faceUVs[1].y);
        tess.vertexUV(v2, faceUVs[2].x, faceUVs[2].y);
        tess.vertexUV(v3, faceUVs[3].x, faceUVs[3].y);
    }

    stack.pop();
}

void TessellateNode(const Geometry::Node& node, Tessellator& tess, float texW, float texH, MatrixStack& stack) {
    auto ref = stack.push();

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