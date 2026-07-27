#pragma once
#include <vector>
#include <array>
#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"

// Clear semantic alias for a triangle face (3 vertex indices)
using TriangleFace = std::array<unsigned int, 3>;

class GameObject {
public:
    std::vector<Vector3> vertices;
    std::vector<TriangleFace> indices; // Wireframe line indices
    Vector3 position = { 0.0f, 0.0f, 0.0f };
    Vector3 rotation = { 0.0f, 0.0f, 0.0f };

    virtual ~GameObject() = default;

    // Base tick method — overridden by derived scripts
    virtual void Update(float deltaTime) {}

    Matrix4x4 GetModelMatrix() const {
        return CreateTranslationMatrix(position.x, position.y, position.z) *
               CreateRotationMatrixX(rotation.x) *
               CreateRotationMatrixY(rotation.y);
    }
};