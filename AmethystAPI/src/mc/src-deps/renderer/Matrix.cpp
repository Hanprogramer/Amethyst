#include "mc/src-deps/renderer/Matrix.hpp"
#include "Matrix.hpp"
#include <mc/src/common/world/phys/Vec3.hpp>

Matrix Matrix::IDENTITY = Matrix();

void Matrix::translate(const Vec3& vec) 
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(vec.x, vec.y, vec.z));
    _m = translationMatrix * _m;  // PRE-MULTIPLY
}

void Matrix::translate(float x, float y, float z) 
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    _m = translationMatrix * _m;  // PRE-MULTIPLY
}

void Matrix::scale(float allAxis) {
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(allAxis, allAxis, allAxis));
    _m = scaleMatrix * _m;  // PRE-MULTIPLY
}

void Matrix::scale(const Vec3& scale) {
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));
    _m = scaleMatrix * _m;  // PRE-MULTIPLY
}

void Matrix::scale(float scaleX, float scaleY, float scaleZ)
{
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, scaleZ));
    _m = scaleMatrix * _m;  // PRE-MULTIPLY
}

void Matrix::rotate(float angle, float x, float y, float z)
{
    // MC expects degrees, GLM rotates counter-clockwise
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(x, y, z));
    _m = rotationMatrix * _m;  // PRE-MULTIPLY
}

void Matrix::rotateRad(float angleRad, float x, float y, float z) {
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angleRad, glm::vec3(x, y, z));
    _m = rotationMatrix * _m;  // PRE-MULTIPLY
}

void Matrix::rotateXDegrees(float angle) {
    rotate(angle, 1.0f, 0.0f, 0.0f);
}

void Matrix::rotateYDegrees(float angle) {
    rotate(angle, 0.0f, 1.0f, 0.0f);
}

void Matrix::rotateZDegrees(float angle) {
    rotate(angle, 0.0f, 0.0f, 1.0f);
}

void Matrix::rotateXRadians(float angleRad) {
    rotateRad(angleRad, 1.0f, 0.0f, 0.0f);
}

void Matrix::rotateYRadians(float angleRad) {
    rotateRad(angleRad, 0.0f, 1.0f, 0.0f);
}

void Matrix::rotateZRadians(float angleRad) {
    rotateRad(angleRad, 0.0f, 0.0f, 1.0f);
}

Vec3 Matrix::operator*(const Vec3& v) const {
    glm::vec4 res = _m * glm::vec4(v.x, v.y, v.z, 1.0f);
    return Vec3(res.x, res.y, res.z);
}