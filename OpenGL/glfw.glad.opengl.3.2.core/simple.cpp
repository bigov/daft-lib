#include <stdio.h>

#ifdef _WIN32
  #define APIENTRY __stdcall
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <linmath.h>
#include "shaders.h"

#define POINTER(i) reinterpret_cast<const GLvoid*>(i)
GLuint hdl_VAO;

static const struct
{
    float x, y;
    float r, g, b;
} vertices[4] =
{
    { -0.6f, -0.6f, 1.f, 0.f, 0.f },
    {  0.6f, -0.6f, 0.f, 1.f, 0.f },
    { -0.6f,  0.6f, 0.f, 0.f, 1.f },
    {  0.6f,  0.6f, 0.f, 0.f, 1.f }
};

static void error_callback(int, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int, int action, int)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 0);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);

    //extern struct gladGLversionStruct GLVersion;
    if(!gladLoadGL()) { exit(-1); }
    printf("OpenGL Version %d.%d loaded", GLVersion.major, GLVersion.minor);

    glfwSwapInterval(1);

    // NOTE: OpenGL error checks have been omitted for brevity

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    glGenVertexArrays(1, &hdl_VAO);
    glBindVertexArray(hdl_VAO);

    glEnableVertexAttribArray(static_cast<GLuint>(vpos_location));

    glVertexAttribPointer(static_cast<GLuint>(vpos_location), 2, GL_FLOAT,
      GL_FALSE, sizeof(float) * 5, POINTER(0));

    glEnableVertexAttribArray(static_cast<GLuint>(vcol_location));

    glVertexAttribPointer(static_cast<GLuint>(vcol_location), 3, GL_FLOAT,
      GL_FALSE, sizeof(float) * 5, POINTER(sizeof(float) * 2));

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        mat4x4 m, p, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = static_cast<float>(width)/static_cast<float>(height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, static_cast<GLfloat>(glfwGetTime()));
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, mvp[0]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
