#pragma once
#include <vector>
#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"

class GameObject {
public:
    std::vector<Vector3> vertices;
    std::vector<std::pair<int, int>> indices; // Wireframe line indices
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