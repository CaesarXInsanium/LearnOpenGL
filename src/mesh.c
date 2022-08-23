#include "mesh.h"
#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

Mesh *Mesh_new(GLfloat *vertices, GLuint *indices, GLuint vertexCount,
               GLuint perVertexValueCount) {
  Mesh *mesh = (Mesh *)malloc(sizeof(Mesh));

  unsigned int VBO, EBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s). This binding is remember as we do
  // other things.
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // sets bufer type, size of entire array in bytes, pointer to array, and
  // read/write permissions
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(GLfloat) * vertexCount * perVertexValueCount, vertices,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * vertexCount, indices,
               GL_STATIC_DRAW);
  // do this after declaring the VBO and EBO
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        perVertexValueCount * sizeof(GLfloat), (void *)0);
  glEnableVertexAttribArray(0);
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
  //                       perVertexValueCount * sizeof(GLfloat),
  //                       (void *)(3 * sizeof(GLfloat)));
  // glEnableVertexAttribArray(1);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                        perVertexValueCount * sizeof(GLfloat),
                        (void *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // note that this is allowed, the call to glVertexAttribPointer registered VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can
  // safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally
  // modify this VAO, but this rarely happens. Modifying other VAOs requires a
  // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
  // VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  mesh->VAO = VAO;
  mesh->VBO = VBO;
  mesh->EBO = EBO;
  mesh->count = vertexCount;
  return mesh;
}
int Mesh_draw(Mesh *mesh, GLvoid *instances) {
  glBindVertexArray(mesh->VAO); // seeing as we only have a single VAO there's
                                // no need to bind it every time, but we'll do
                                // so to keep things a bit more organized
  glDrawElements(GL_TRIANGLES, mesh->count, GL_UNSIGNED_INT, instances);
  return EXIT_SUCCESS;
}
int Mesh_destroy(Mesh *mesh) {
  glDeleteVertexArrays(1, &mesh->VAO);
  glDeleteBuffers(1, &mesh->VBO);
  free(mesh);
  return 0;
}
