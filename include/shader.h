#ifndef SHADER_H
#define SHADER_H
#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// stolen from:
// https://stackoverflow.com/questions/2029103/correct-way-to-read-a-text-file-into-a-buffer-in-c
char *loadSourceFile(const char *path);
GLuint ShaderProgram_fromChar(const char *vertexShader,
                              const char *fragmentShader);

#endif
