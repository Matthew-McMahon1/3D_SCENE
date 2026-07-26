#pragma once
#include <cmath>
#include "../Math/Matrix4x4.h"

class Camera {
public:
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    Camera(float fovDegrees, float aspect, float nearP, float farP)
        : fov(fovDegrees), aspectRatio(aspect), nearPlane(nearP), farPlane(farP) {}

    Matrix4x4 GetProjectionMatrix() const {
        Matrix4x4 mat;
        float fovRad = fov * (3.14159265f / 180.0f);
        float tanHalfFov = std::tan(fovRad / 2.0f);

        mat.m[0][0] = 1.0f / (aspectRatio * tanHalfFov);
        mat.m[1][1] = 1.0f / tanHalfFov;
        mat.m[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
        mat.m[2][3] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
        mat.m[3][2] = -1.0f;
        mat.m[3][3] = 0.0f;

        return mat;
    }
};