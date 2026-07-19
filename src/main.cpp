#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

// Define constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PI = 3.14159265359f;

// 1. Core Data Layout Structures
struct Vector3 {
    float x, y, z;
};

struct Vector4 {
    float x, y, z, w;
};

struct Edge {
    int startIdx;
    int endIdx;
};

struct Matrix4x4 {
    float m[4][4] = {0};
};

// 2. Linear Algebra Matrix Operations Helper Utilities
Vector4 MultiplyMatrixVector(const Matrix4x4& mat, const Vector3& vec) {
    Vector4 out;
    out.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0];
    out.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1];
    out.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2];
    out.w = vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + mat.m[3][3];
    return out;
}

Matrix4x4 CreatePerspectiveMatrix(float fovDegrees, float aspectRatio, float nearPlane, float farPlane) {
    Matrix4x4 mat;
    float fovRadians = fovDegrees * (PI / 180.0f);
    float tanHalfFov = std::tan(fovRadians / 2.0f);

    mat.m[0][0] = 1.0f / (aspectRatio * tanHalfFov);
    mat.m[1][1] = 1.0f / tanHalfFov;
    mat.m[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
    mat.m[2][3] = -1.0f;
    mat.m[3][2] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
    return mat;
}

// 3. Main Loop and Application Thread Execution
int main() {
    if (!glfwInit()) {
        std::cerr << "CRITICAL: Failed to initialize GLFW framework runtime.\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pure Math 3D Engine Sandbox", NULL, NULL);
    if (!window) {
        std::cerr << "CRITICAL: Failed to generate system viewport window allocation.\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Geometry Definitions: Create standard coordinates for a localized 3D cube bounding box
    std::vector<Vector3> cubeVertices = {
        {-1.0f, -1.0f, -1.0f}, { 1.0f, -1.0f, -1.0f}, { 1.0f,  1.0f, -1.0f}, {-1.0f,  1.0f, -1.0f},
        {-1.0f, -1.0f,  1.0f}, { 1.0f, -1.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}, {-1.0f,  1.0f,  1.0f}
    };

    // Index Map establishing structural linkage between matching face vertices
    std::vector<Edge> cubeEdges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Back face index mapping
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Front face index mapping
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Interconnecting bridge structure paths
    };

    // Pre-calculate Projection System Settings
    float aspect = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
    Matrix4x4 projMatrix = CreatePerspectiveMatrix(60.0f, aspect, 0.1f, 100.0f);

    // Active Loop System Frame Thread
    while (!glfwWindowShouldClose(window)) {
        // Clear frame buffer to slate gray color profile
        glClearColor(0.12f, 0.14f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Calculate dynamic mathematical delta angle variables based on chronological application runtime
        float timeTime = static_cast<float>(glfwGetTime());
        float angleX = timeTime * 0.6f;
        float angleY = timeTime * 0.3f;

        // Populate rotational object matrices
        Matrix4x4 rotXMatrix, rotYMatrix;
        rotXMatrix.m[0][0] = 1.0f; rotXMatrix.m[1][1] = std::cos(angleX); rotXMatrix.m[1][2] = -std::sin(angleX);
        rotXMatrix.m[2][1] = std::sin(angleX); rotXMatrix.m[2][2] = std::cos(angleX); rotXMatrix.m[3][3] = 1.0f;

        rotYMatrix.m[0][0] = std::cos(angleY); rotYMatrix.m[0][2] = std::sin(angleY); rotYMatrix.m[1][1] = 1.0f;
        rotYMatrix.m[2][0] = -std::sin(angleY); rotYMatrix.m[2][2] = std::cos(angleY); rotYMatrix.m[3][3] = 1.0f;

        // Project and collect current operational geometric indices array frames 
        std::vector<Vector3> projectedScreenPoints;
        for (const auto& vertex : cubeVertices) {
            // Apply Model Rotation manual operations
            Vector4 rotatedVector = MultiplyMatrixVector(rotXMatrix, vertex);
            Vector3 rotatedPos = {rotatedVector.x, rotatedVector.y, rotatedVector.z};
            rotatedVector = MultiplyMatrixVector(rotYMatrix, rotatedPos);

            // Shift Object backwards along the -Z axis away from Camera focal path (Simulating view mapping offsets)
            rotatedVector.z -= 4.5f;

            // Apply Projection Matrix calculations
            Vector4 clipSpace = MultiplyMatrixVector(projMatrix, {rotatedVector.x, rotatedVector.y, rotatedVector.z});

            // Perform hardware Perspective Divide calculations to calculate absolute NDC array coordinates
            if (clipSpace.w != 0.0f) {
                clipSpace.x /= clipSpace.w;
                clipSpace.y /= clipSpace.w;
            }
            projectedScreenPoints.push_back({clipSpace.x, clipSpace.y, 0.0f});
        }

        // Display Render Loop operations paths mapping onto final frame canvas layout
        glLineWidth(2.5f);
        glBegin(GL_LINES);
        glColor3f(0.38f, 0.68f, 0.93f); // Clean digital engineering neon blue color track selection
        for (const auto& edge : cubeEdges) {
            glVertex2f(projectedScreenPoints[edge.startIdx].x, projectedScreenPoints[edge.startIdx].y);
            glVertex2f(projectedScreenPoints[edge.endIdx].x, projectedScreenPoints[edge.endIdx].y);
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}