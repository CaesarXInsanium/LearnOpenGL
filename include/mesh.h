#ifndef MESH_H
#define MESH_H
#include "glad/gl.h"
#include <GLFW/glfw3.h>

typedef struct Mesh_ {
  GLuint VBO;
  GLuint EBO;
  GLuint VAO;
  GLuint count;
} Mesh;

Mesh Mesh_new(GLfloat *vertices, GLuint *indices, GLuint count);
int Mesh_draw(Mesh *mesh, GLvoid *instances);
int Mesh_destroy(Mesh mesh);

#endif
