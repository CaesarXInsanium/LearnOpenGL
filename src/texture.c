#include "texture.h"
#include "glad/gl.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GLFW/glfw3.h>

Texture Texture_null(void) {
  Texture self;
  self.id = 0;
  self.index = INT_MAX;
  return self;
}
TextureData *TextureData_new(GLuint count) {
  TextureData *self = (TextureData *)malloc(sizeof(TextureData));
  self->count = count;
  self->textures = (Texture *)malloc(sizeof(Texture) * count);
  for (GLuint i = 0; i < count; i++) {
    self->textures[i] = Texture_null();
  }
  return self;
}
void TextureData_destroy(TextureData *self);
