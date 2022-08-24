#include "glad/gl.h"
#include <GLFW/glfw3.h>
#pragma once

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

typedef struct App {
  GLFWwindow *window;
  GLuint width;
  GLuint height;
} App;

App *App_new(const char *name, const int width, const int height);
int App_should_close(App *self);
void App_set_resize_callback(App *self,
                             void (*callback)(GLFWwindow *window, int width,
                                              int height));
void App_handle_events(App *self);
void App_handle_inputs(App *self);
GLfloat App_fov(App *self);
void App_destroy(App *self);
