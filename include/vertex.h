#include "glad/gl.h"
#include <GLFW/glfw3.h>
#pragma once

typedef struct Vertex_ {
  GLfloat position[3];
  GLfloat color[3];
  GLfloat texCoords[2];
} Vertex;
