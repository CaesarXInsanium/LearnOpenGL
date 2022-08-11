#include "glad/gl.h"
#include "mesh.h"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFT Window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGL(glfwGetProcAddress)) {
    puts("Failed to init GLAD");
    return -1;
  }

  char *vertexShaderSource = loadSourceFile("shaders/vertex.glsl");
  char *fragmentShaderSource = loadSourceFile("shaders/fragment.glsl");
  GLuint shaderProgram =
      ShaderProgram_fromChar(vertexShaderSource, fragmentShaderSource);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices01[] = {
      -0.5f, 0.0f, 0.0f, // top right
      0.0f,  0.5f, 0.0f, // bottom right
      0.5f,  0.0f, 0.0f, // bottom left
  };

  unsigned int indices01[] = {0, 1, 2};
  int count01 = 3;
  Mesh *mesh01 = Mesh_new(vertices01, indices01, count01);

  float vertices02[] = {
      0.7f, 0.1f,  0.0f, // top right
      0.2f, -0.6f, 0.0f, // bottom right
      0.2f, 0.6f,  0.0f, // bottom left
  };
  Mesh *mesh02 = Mesh_new(vertices02, indices01, count01);

  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window)) {
    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Uniforms
    GLfloat timeValue = glfwGetTime();
    GLfloat greenValue = (sin(timeValue) / 2.0f) + 0.5;
    GLint vertexColorlocation = glGetUniformLocation(shaderProgram, "ourColor");

    // draw our first triangle
    glUseProgram(shaderProgram);
    glUniform4f(vertexColorlocation, 0.0f, greenValue, 0.0f, 1.0f);

    Mesh_draw(mesh01, 0);
    Mesh_draw(mesh02, 0);
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  Mesh_destroy(mesh01);
  Mesh_destroy(mesh02);
  glDeleteProgram(shaderProgram);

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
