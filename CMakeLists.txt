cmake_minimum_required(VERSION 4.0)
project(OpenGLCourse)
cmake_policy(SET CMP0072 NEW)

file(COPY "${CMAKE_SOURCE_DIR}/Resource" DESTINATION "${CMAKE_BINARY_DIR}/Resource")

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCE "*.cpp" ".h")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLM REQUIRED)
find_package(ASSIMP REQUIRED)

add_executable(OpenGLCourse main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)