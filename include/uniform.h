#ifndef UNIFORM_H
#define UNIFORM_H
#include "glad/gl.h"
#include "mesh.h"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum UniformDataType_ {
  FLOAT1,
  FLOAT2,
  FLOAT3,
  FLOAT4,
  MAT4,
} UniformDataType;

typedef struct UniformInfo_ {
  char *name;
  GLint location;
  void *value;
  UniformDataType type;
} UniformInfo;

typedef struct Uniforms_ {
  GLuint count;
  UniformInfo *data;
} Uniforms;

#endif
