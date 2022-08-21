#include <cglm/struct/affine.h>
#define STB_IMAGE_IMPLEMENTATION
#include "glad/gl.h"
#include "mesh.h"
#include "shader.h"
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <cglm/common.h>
#include <cglm/mat4.h>
#include <cglm/vec4.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#define M_PI 3.14159265358979323846264338327950288
#define glm_radians(angleInDegrees) ((angleInDegrees)*M_PI / 180.0)

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

int main() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW Window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  if (!gladLoadGL(glfwGetProcAddress)) {
    puts("Failed to init GLAD");
    return -1;
  }

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
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
  };

  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  GLuint vertexCount = 6;
  GLuint perVertexValueCount = 8;

  Mesh *mesh = Mesh_new(vertices, indices, vertexCount, perVertexValueCount);

  // Matrices

  // render loop
  Shader_use(shader);
  Shader_setInt(shader, "texture1", 0);
  Shader_setInt(shader, "texture2", 1);
  while (!glfwWindowShouldClose(window)) {
    // input

    processInput(window);

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
    mat4 transform_matrix = {
        {1.0, 1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0, 1.0},
    };
    glm_mat4_identity(transform_matrix);

    vec3 axis = {0.0, 0.0, 1.0};
    glm_rotate(transform_matrix, glm_radians((float)glfwGetTimerValue()), axis);

    vec3 translation = {0.5, -0.5, 0.0};
    glm_translate(transform_matrix, translation);
    float scale_factor = 0.5;
    glm_mat4_scale(transform_matrix, scale_factor);

    Shader_setMat4(shader, "transform", (GLfloat *)transform_matrix);
    Mesh_draw(mesh, 0);
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  Mesh_destroy(mesh);
  Shader_destroy(shader);
  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  printf("Window Framebuffer Size Callback:\t%p\n", (void *)window);
  glViewport(0, 0, width, height);
}
