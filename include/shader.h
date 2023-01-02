#ifndef SHADER_H
#define SHADER_H
#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Shader_ {
  GLuint ID;
} Shader;

Shader *Shader_new(const char *vertexPath, const char *fragmentPath);
int Shader_destroy(Shader *self);

void Shader_use(Shader *self);

void Shader_setBool(Shader *self, const char *name, bool value);
void Shader_setFloat(Shader *self, const char *name, GLfloat value);
void Shader_setInt(Shader *self, const char *name, GLint value);
void Shader_setMat4(Shader *self, const char *name, GLfloat *value);

// stolen from:
// https://stackoverflow.com/questions/2029103/correct-way-to-read-a-text-file-into-a-buffer-in-c
char *loadSourceFile(const char *path);
GLuint GLShaderProgram_from_char(const char *vertexShader,
                                const char *fragmentShader);

#endif
