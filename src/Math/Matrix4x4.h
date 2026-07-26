#pragma once
#include <cmath>
#include "Vector3.h"

struct Matrix4x4 {
    float m[4][4] = { 0 };

    Matrix4x4() {
        // Default to identity matrix
        m[0][0] = 1.0f; m[1][1] = 1.0f; m[2][2] = 1.0f; m[3][3] = 1.0f;
    }

    // Matrix-Matrix Multiplication
    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                result.m[row][col] = 0.0f;
                for (int k = 0; k < 4; ++k) {
                    result.m[row][col] += m[row][k] * other.m[k][col];
                }
            }
        }
        return result;
    }

    // Matrix-Vector Transformation (Homogeneous Coordinates)
    Vector3 Transform(const Vector3& v) const {
        float x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + m[0][3];
        float y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + m[1][3];
        float z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + m[2][3];
        float w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + m[3][3];

        if (w != 0.0f && w != 1.0f) {
            x /= w;
            y /= w;
            z /= w;
        }

        return Vector3(x, y, z);
    }
};

// Helper Matrix Factory Functions
inline Matrix4x4 CreateTranslationMatrix(float x, float y, float z) {
    Matrix4x4 mat;
    mat.m[0][3] = x;
    mat.m[1][3] = y;
    mat.m[2][3] = z;
    return mat;
}

inline Matrix4x4 CreateRotationMatrixX(float angleRadians) {
    Matrix4x4 mat;
    mat.m[1][1] = std::cos(angleRadians);
    mat.m[1][2] = -std::sin(angleRadians);
    mat.m[2][1] = std::sin(angleRadians);
    mat.m[2][2] = std::cos(angleRadians);
    return mat;
}

inline Matrix4x4 CreateRotationMatrixY(float angleRadians) {
    Matrix4x4 mat;
    mat.m[0][0] = std::cos(angleRadians);
    mat.m[0][2] = std::sin(angleRadians);
    mat.m[2][0] = -std::sin(angleRadians);
    mat.m[2][2] = std::cos(angleRadians);
    return mat;
}