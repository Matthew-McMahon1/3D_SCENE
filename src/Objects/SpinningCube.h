#pragma once
#include "GameObject.h"

class SpinningCube : public GameObject {
public:
    float spinSpeedX = 0.6f;
    float spinSpeedY = 0.3f;

    SpinningCube() {
        // 8 Corners of a unit cube
        vertices = {
            {-1.0f, -1.0f, -1.0f}, { 1.0f, -1.0f, -1.0f}, { 1.0f,  1.0f, -1.0f}, {-1.0f,  1.0f, -1.0f},
            {-1.0f, -1.0f,  1.0f}, { 1.0f, -1.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}, {-1.0f,  1.0f,  1.0f}
        };

        // 12 Line connections for wireframe rendering
        indices = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Back face
            {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Front face
            {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
        };
    }

    void Update(float deltaTime) override {
        rotation.x += spinSpeedX * deltaTime;
        rotation.y += spinSpeedY * deltaTime;
    }
};