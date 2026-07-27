#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "Math/Vector3.h"
#include "Math/Matrix4x4.h"
#include "Graphics/Camera.h"
#include "Objects/Cube/SpinningCube.h"
#include "Objects/Cube/BouncingCube.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void DrawObjectWireframe(const GameObject& obj, const Matrix4x4& mvp) {
    glBegin(GL_LINES);
    glColor3f(0.2f, 0.8f, 1.0f); // Cyan wireframe lines

    for (const auto& edge : obj.indices) {
        Vector3 v1 = mvp.Transform(obj.vertices[edge.first]);
        Vector3 v2 = mvp.Transform(obj.vertices[edge.second]);

        glVertex2f(v1.x, v1.y);
        glVertex2f(v2.x, v2.y);
    }
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3D Engine Architecture", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Setup Camera
    float aspect = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
    Camera camera(60.0f, aspect, 0.1f, 100.0f);

    // Scene Graph / World Objects List
    std::vector<std::unique_ptr<GameObject>> sceneObjects;

    // Create Left Cube (Standard Spin)
    auto leftCube = std::make_unique<SpinningCube>();
    leftCube->position = { -2.0f, 0.0f, -6.0f };
    sceneObjects.push_back(std::move(leftCube));

    // Create Right Cube (Standard Bounce)
    auto rightCube = std::make_unique<BouncingCube>();
    rightCube->position = { 2.0f, 0.0f, -6.0f };
    sceneObjects.push_back(std::move(rightCube));

    float lastFrameTime = static_cast<float>(glfwGetTime());

    // Application Frame Loop
    while (!glfwWindowShouldClose(window)) {
        // 1. Delta Time Calculation
        float currentFrameTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // 2. Handle Resizing Dynamically
        int displayW, displayH;
        glfwGetFramebufferSize(window, &displayW, &displayH);

        // Prevent division by zero when window is minimized
        if (displayH > 0) {
            // Tell OpenGL to render to the entire new framebuffer area
            glViewport(0, 0, displayW, displayH);

            // Keep correct aspect ratio on camera
            float currentAspect = static_cast<float>(displayW) / static_cast<float>(displayH);
            camera.aspectRatio = currentAspect;
        }

        // 2. Clear Frame
        glClearColor(0.12f, 0.14f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Matrix4x4 projMatrix = camera.GetProjectionMatrix();

        // 3. Update & Render All Scene Objects
        for (const auto& obj : sceneObjects) {
            obj->Update(deltaTime);

            Matrix4x4 mvp = projMatrix * obj->GetModelMatrix();
            DrawObjectWireframe(*obj, mvp);
        }

        // 4. Swap Display Canvas
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}