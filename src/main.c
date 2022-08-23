#include <cglm/struct/affine.h>
#define STB_IMAGE_IMPLEMENTATION
#include "app.h"
#include "glad/gl.h"
#include "mesh.h"
#include "shader.h"
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <cglm/cam.h>
#include <cglm/cglm.h>
#include <cglm/common.h>
#include <cglm/mat4.h>
#include <cglm/vec4.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#define M_PI 3.14159265358979323846264338327950288
#define glm_radians(angleInDegrees) ((angleInDegrees)*M_PI / 180.0)

// settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main() {
  // glfw: initialize and configure
  // ------------------------------
  App *app = App_new("LearnOpenGL", WIDTH, HEIGHT);
  App_set_resize_callback(app, framebuffer_size_callback);

  Shader *shader = Shader_new("shaders/vertex.glsl", "shaders/fragment.glsl");
  // Textures
  GLuint texture1, texture2;

  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  // s and t denotes coordinate positions of the textures
  // sets wrapping behaviours for dimensions beyond normalized positions
  // for s and t axis
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // denotes which colors each pixel will be given the coodirnates and nearest
  // texel
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_set_flip_vertically_on_load(true);

  GLint width, height, nrChannels;
  unsigned char *data0 =
      stbi_load("images/container.jpg", &width, &height, &nrChannels, 0);
  if (data0) {

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data0);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  stbi_image_free(data0);

  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLint width1, height1, nrChannels1;
  unsigned char *data1 =
      stbi_load("images/awesomeface.png", &width1, &height1, &nrChannels1, 0);
  if (data1) {

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data1);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  stbi_image_free(data1);
  // set up vertex data (and buffer(s)) and configure vertex attributes
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

  unsigned int indices[] = {
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
      18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
  };
  GLuint vertexCount = 36;
  GLuint perVertexValueCount = 5;

  Mesh *mesh = Mesh_new(vertices, indices, vertexCount, perVertexValueCount);

  // Matrices

  // render loop
  Shader_use(shader);
  Shader_setInt(shader, "texture1", 0);
  Shader_setInt(shader, "texture2", 1);
  while (!App_should_close(app)) {
    App_handle_inputs(app);
    // render

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    Shader_use(shader);

    // transforms
    mat4 model_matrix = GLM_MAT4_IDENTITY_INIT;
    vec3 model_axis = {0.5, 1.0, 0.0};
    glm_rotate(model_matrix, glm_radians((GLfloat)glfwGetTimerValue() * glm_radians(50.0)), model_axis);

    mat4 view_matrix = GLM_MAT4_IDENTITY_INIT;
    vec3 view_translation = {0.0, 0.0, -3.0};
    glm_translate(view_matrix, view_translation);

    mat4 projection_matrix = GLM_MAT4_IDENTITY_INIT;
    glm_perspective(glm_radians(45.0), WIDTH / HEIGHT, 0.1, 100.0,
                    projection_matrix);

    Shader_setMat4(shader, "model", (GLfloat *)model_matrix);
    Shader_setMat4(shader, "view", (GLfloat *)view_matrix);
    Shader_setMat4(shader, "projection", (GLfloat *)projection_matrix);
    Mesh_draw(mesh, 0);

    mat4 other_matrix = GLM_MAT4_IDENTITY_INIT;
    GLfloat s = (GLfloat)glfwGetTimerValue();
    glm_mat4_scale(other_matrix, sinf(s));
    Shader_setMat4(shader, "transform", (GLfloat *)other_matrix);
    Mesh_draw(mesh, 0);

    App_handle_events(app);
  }
  Mesh_destroy(mesh);
  Shader_destroy(shader);
  App_destroy(app);
  return 0;
}
