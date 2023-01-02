project(
  'LearnOpenGL',
  'c',
  version: '0.0.1',
  default_options: [
    'warning_level=3',
    'werror=true',
    'buildtype=debugoptimized',
    'debug=true',
    #'optimization=3',
    'c_std=c18'
  ]
)
  
SRC = [
  'src/main.c',
  'src/gl.c',
  'src/mesh.c',
  'src/shader.c',
  'src/app.c',
  #'src/texture.c',
  ]
INC = include_directories('include')

DEPS = [
  dependency('cglm'),
  dependency('glfw3')
  ]

BIN = executable(
  'learn',
  SRC,
  include_directories: INC,
  dependencies: DEPS,
  )
