#include "app.h"
#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

App *current_app = NULL;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  printf("Window Framebuffer Size Callback:\t%p\n", (void *)window);
  current_app->width = width;
  current_app->height = height;
  glViewport(0, 0, width, height);
}

App *App_new(const char *name, const int width, const int height) {
  App *self = (App *)malloc(sizeof(App));
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW Window\n");
    glfwTerminate();
    exit(1);
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGL(glfwGetProcAddress)) {
    puts("Failed to init GLAD");
    exit(1);
  }
  glEnable(GL_DEPTH_TEST);
  self->window = window;
  self->width = width;
  self->height = height;
  current_app = self;
  return self;
}
void App_focus(App *app) { current_app = app; }
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

inline GLfloat App_fov(App *self) {
  return (GLfloat)self->width / (GLfloat)self->height;
}
void App_destroy(App *self) {
  glfwTerminate();
  free(self);
}
