#pragma once
#include "Cube.h"
#include <cmath>

class BouncingCube : public Cube {
public:
    float bounceSpeed = 1.5f;
    float totalTime = 0;

    BouncingCube() = default;

    // Initialize custom speeds
    BouncingCube(float bounceSpeed)
        : bounceSpeed(bounceSpeed) {}

    void Update(float deltaTime) override {
        totalTime += deltaTime;
        position.y = std::sin(bounceSpeed * totalTime);
    }
};