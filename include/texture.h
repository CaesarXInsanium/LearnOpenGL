#pragma once
#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>

typedef struct Texture_ {
  GLuint index;
  GLuint id;
} Texture;

Texture Texture_null(void);

typedef struct TextureData_ {
  Texture *textures;
  GLuint count;
} TextureData;

TextureData *TextureData_new(GLuint count);
void TextureData_destroy(TextureData *self);

int LoadTexture(GLuint index, GLuint *id, const char *path, GLuint color_mode,
                GLuint wrap_method, GLuint min_mag);
