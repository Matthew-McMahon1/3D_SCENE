#pragma once
#include "Cube.h"

class SpinningCube : public Cube {
public:
    float spinSpeedX = 0.6f;
    float spinSpeedY = 0.3f;

    SpinningCube() = default;

    // Initialize custom speeds
    SpinningCube(float spinSpeedX, float spinSpeedY)
        : spinSpeedX(spinSpeedX), spinSpeedY(spinSpeedY) {}

    void Update(float deltaTime) override {
        rotation.x += spinSpeedX * deltaTime;
        rotation.y += spinSpeedY * deltaTime;
    }
};