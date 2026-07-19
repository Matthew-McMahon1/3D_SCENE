cmake_minimum_required(VERSION 3.15)
project(LidarSim3D VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Declare the executable first
add_executable(LidarSim src/main.cpp)

# 2. Tell CMake to look at the 'include' folder right in your root directory
target_include_directories(LidarSim PRIVATE "${CMAKE_SOURCE_DIR}/include")

# 3. Link the 'lib-vc2022' folder library right in your root directory
target_link_libraries(LidarSim PRIVATE 
    "${CMAKE_SOURCE_DIR}/lib-vc2022/glfw3.lib"
    Opengl32.lib
)