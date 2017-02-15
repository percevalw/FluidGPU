//
// Created by Perceval Wajsburt on 11/02/2017.
//

#ifndef FLUIDGPU_GL_H
#define FLUIDGPU_GL_H

#endif //FLUIDGPU_GL_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <vector>

#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif