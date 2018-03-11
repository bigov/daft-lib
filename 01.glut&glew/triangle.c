/**

 Start from:

   https://en.wikibooks.org/wiki/OpenGL_Programming
   https://ru.wikibooks.org/wiki/OpenGL_%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5/%D0%92%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5_%D0%B2_%D1%81%D0%BE%D0%B2%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%BD%D1%8B%D0%B9_OpenGL

*/

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
/**
$ pkg-config --cflags --libs glew
-I/usr/include/libdrm -lGLEW -lGLU -lGL 
*/

#include <GL/freeglut.h>

GLuint program;
GLint attribute_coord2d;

/* Создание и компиляция шейдерной программы*/
int init_resources(void)
{
  GLint compile_ok = GL_FALSE;
  GLint link_ok = GL_FALSE;

  // создание вершинного шэйдера
  const char *vs_source =
    "#version 120\n                           "
    "attribute vec2 coord2d;                  "
    "void main(void) {                        "
    "  gl_Position = vec4(coord2d, 0.0, 1.0); "
    "}                                        ";
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vs_source, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
  if (0 == compile_ok)
  {
    fprintf(stderr, "Error in vertex shader\n");
    return 0;
  }

  // Создание фрагментного шейдера
  const char *fs_source =
    "#version 120\n           "
    "void main(void) {        "
    "  gl_FragColor[0] = 0.0; "
    "  gl_FragColor[1] = 0.0; "
    "  gl_FragColor[2] = 1.0; "
    "}                        ";
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fs_source, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
  if (!compile_ok) {
    fprintf(stderr, "Error in fragment shader\n");
    return 0;
  }

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    fprintf(stderr, "glLinkProgram:");
    return 0;
  }

  const char* attribute_name = "coord2d"; // имя атрибута для привязки к
                                          // программе вершинного шейдера -
                                          // координаты текущей вершины.
  attribute_coord2d = glGetAttribLocation(program, attribute_name);
  if (-1 == attribute_coord2d) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return 0;
  }
    
  return 1;
}

/* функция рисования изображения*/
void onDisplay(void) {
  glClearColor(0.85, 0.85, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // нарисовать треугольник используя шейдерную программу
  glUseProgram(program);
  glEnableVertexAttribArray(attribute_coord2d);
  GLfloat triangle_vertices[] = { 0.0,  0.8, -0.8, -0.8, 0.8, -0.8 };
  glVertexAttribPointer(
    attribute_coord2d, // атрибут
    2,                 // количество элементов на вершине, здесь две - (х, у).
    GL_FLOAT,          // тип каждого элемента
    GL_FALSE,          // принять наши параметры как есть
    0,                 // никаких дополнительных данных между каждой позицией
    triangle_vertices  // указатель на массив C.
    );
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(attribute_coord2d);

  glutSwapBuffers();
  return;
}

void free_resources(void) {
  glDeleteProgram(program);
  return;
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Hi from GLUT");

  /* init extension wrangler */
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK)
  {
    fprintf(stderr, "Error: %s\n\n", glewGetErrorString(glew_status));
    return EXIT_FAILURE;
  }

  if (1 == init_resources())
  {
    glutDisplayFunc(onDisplay);
    glutMainLoop();
  }

  free_resources();
  return EXIT_SUCCESS;
}
