#pragma once
#include "../GameObject.h"

class Cube : public GameObject {
public:
    Cube() {
        // 8 Corners of a unit cube
        // 
        vertices = {
            {-1.0f, -1.0f, -1.0f}, { 1.0f, -1.0f, -1.0f}, { 1.0f,  1.0f, -1.0f}, {-1.0f,  1.0f, -1.0f},
            {-1.0f, -1.0f,  1.0f}, { 1.0f, -1.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}, {-1.0f,  1.0f,  1.0f}
        };

        // 12 Triangular faces (2 per side) using Counter-Clockwise (CCW) winding
        indices = {
            // Front Face (z = +1.0)
            TriangleFace{4, 5, 6}, TriangleFace{4, 6, 7},
            // Back Face (z = -1.0)
            TriangleFace{1, 0, 3}, TriangleFace{1, 3, 2},
            // Top Face (y = +1.0)
            TriangleFace{3, 2, 6}, TriangleFace{3, 6, 7},
            // Bottom Face (y = -1.0)
            TriangleFace{4, 1, 0}, TriangleFace{4, 5, 1},
            // Right Face (x = +1.0)
            TriangleFace{5, 1, 2}, TriangleFace{5, 2, 6},
            // Left Face (x = -1.0)
            TriangleFace{0, 4, 7}, TriangleFace{0, 7, 3}
        };
    };
};