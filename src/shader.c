#include "shader.h"
#include "glad/gl.h"
#include <GLFW/glfw3.h>

Shader *Shader_new(const char *vertexPath, const char *fragmentPath) {
  Shader *self = (Shader *)malloc(sizeof(Shader));
  char *vertexShaderSource = loadSourceFile(vertexPath);
  char *fragmentShaderSource = loadSourceFile(fragmentPath);
  GLuint shaderProgram =
      GLShaderProgram_fromChar(vertexShaderSource, fragmentShaderSource);

  self->ID = shaderProgram;
  return self;
}
int Shader_destroy(Shader *self) {
  glDeleteProgram(self->ID);
  free(self);
  return EXIT_SUCCESS;
}

void Shader_use(Shader *self) { glUseProgram(self->ID); }

void Shader_setBool(Shader *self, const char *name, bool value) {
  glUniform1i(glGetUniformLocation(self->ID, name), (int)value);
}
void Shader_setFloat(Shader *self, const char *name, GLfloat value) {

  glUniform1f(glGetUniformLocation(self->ID, name), value);
}
void Shader_setInt(Shader *self, const char *name, GLint value) {

  glUniform1i(glGetUniformLocation(self->ID, name), value);
}

char *loadSourceFile(const char *path) {
  char *source = NULL;
  FILE *fp = fopen(path, "r");
  if (fp != NULL) {
    /* Go to the end of the file. */
    if (fseek(fp, 0L, SEEK_END) == 0) {
      /* Get the size of the file. */
      long bufsize = ftell(fp);
      if (bufsize == -1) { /* Error */
      }
      /* Allocate our buffer to that size. */
      source = malloc(sizeof(char) * (bufsize + 1));
      /* Go back to the start of the file. */
      if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */
      }

      /* Read the entire file into memory. */
      size_t newLen = fread(source, sizeof(char), bufsize, fp);
      if (ferror(fp) != 0) {
        fputs("Error reading file", stderr);
      } else {
        source[newLen++] = '\0'; /* Just to be safe. */
      }
    }
    fclose(fp);
  }

  return source;
}

GLuint GLShaderProgram_fromChar(const char *vertexShaderSource,
                                const char *fragmentShaderSource) {

  // build and compile our shader program
  // ------------------------------------
  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("ERRO: Vertex Shader Compilation failed:\t%s\n", infoLog);
  }
  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("ERRO: Fragment Shader Compilation failed:\t%s\n", infoLog);
  }
  // link shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("ERRO: Shader Program linking failed:\t%s\n", infoLog);
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return shaderProgram;
}
