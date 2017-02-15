cmake_minimum_required(VERSION 3.6)

project(FluidGPU)
cmake_policy(SET CMP0004 OLD)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(PROJECT_NAME FluidGPU)
set(CMAKE_CXX_STANDARD 11)
set(mortonlib_DIR mortonlib/include)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLUT_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_gl_INCLUDE_DIR})

set(SOURCE_FILES main.cpp particle_system.cpp particle_system.hpp gl.h simulation.cpp simulation.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(
        ${PROJECT_NAME}
        ${SDL2_LIBRARIES}
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY}
        ${GLUT_LIBRARIES}
        ${GLEW_LIBRARIES})