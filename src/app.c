#include "app.h"
#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  printf("Window Framebuffer Size Callback:\t%p\n", (void *)window);
  glViewport(0, 0, width, height);
}

App *App_new(const char *name, const int width, const int height) {
  App *self = (App *)malloc(sizeof(App));
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW Window\n");
    glfwTerminate();
    exit(1);
  }
  self->window = window;
  glfwMakeContextCurrent(window);
  if (!gladLoadGL(glfwGetProcAddress)) {
    puts("Failed to init GLAD");
    exit(1);
  }
  glEnable(GL_DEPTH_TEST);
  return self;
}
int App_should_close(App *self) { return glfwWindowShouldClose(self->window); }
void App_set_resize_callback(App *self, void(callback)(GLFWwindow *window,
                                                       int width, int height)) {
  glfwSetFramebufferSizeCallback(self->window, callback);
}
void App_handle_events(App *self) {
  glfwSwapBuffers(self->window);
  glfwPollEvents();
}
void App_handle_inputs(App *self) {

  if (glfwGetKey(self->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(self->window, true);
}
void App_destroy(App *self) {
  glfwTerminate();
  free(self);
}
