cmake_minimum_required(VERSION 4.0)
project(OpenGLCourse VERSION 1.0)
cmake_policy(SET CMP0072 NEW)

file(COPY "${CMAKE_SOURCE_DIR}/Resource" DESTINATION "${CMAKE_BINARY_DIR}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(OpenGL REQUIRED)

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

set(LIBS ${GLFW3_LIBRARY} ${ASSIMP_LIBRARY} OpenGL::GL)

file(GLOB SOURCE "src/*.cpp" "src/*.h")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Assimp build tests" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "Assimp install" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "Assimp install PDB" FORCE)

add_executable(${PROJECT_NAME} gl.c glad_loader.h stb_image.cpp main.cpp ${SOURCE})

add_subdirectory(${CMAKE_SOURCE_DIR}/glm)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} ${LIBS})