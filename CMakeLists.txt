cmake_minimum_required(VERSION 4.0)
project(OpenGLCourse)
cmake_policy(SET CMP0072 NEW)

file(COPY "${CMAKE_SOURCE_DIR}/Resource" DESTINATION "${CMAKE_BINARY_DIR}/Resource")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

file(GLOB SOURCE "*.cpp" ".h")

find_package(OpenGL REQUIRED)
#find_package(GLFW3 REQUIRED)
#find_package(GLM REQUIRED)
#find_package(ASSIMP REQUIRED)

add_executable(OpenGLCourse gl.c ${SOURCE})

link_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)