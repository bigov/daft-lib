"""Example 1: white triangle on orange background

setting up a window with OpenGL context and rendering one white triangle on an
orange background using shaders

"""

import ctypes
import sdl2
from OpenGL import GL


def run():

    if sdl2.SDL_Init(sdl2.SDL_INIT_VIDEO) != 0:
        print(sdl2.SDL_GetError())
        return

    window = sdl2.SDL_CreateWindow(
        b"Example 1",
        sdl2.SDL_WINDOWPOS_UNDEFINED, sdl2.SDL_WINDOWPOS_UNDEFINED, 640, 480,
        sdl2.SDL_WINDOW_OPENGL)
    context = sdl2.SDL_GL_CreateContext(window)

    # get Vertex Array Object name
    vao = GL.glGenVertexArrays(1)
    # set this new VAO to the active one
    GL.glBindVertexArray(vao)

    # vertex data for one triangle
    triangle_vertices = [0.0, 0.5, 0.5, -0.5, -0.5, -0.5]

    # convert to ctypes c_float array
    triangle_array = ((ctypes.c_float * len(triangle_vertices))
                      (*triangle_vertices))

    # get a VBO name from the graphics card
    vbo = GL.glGenBuffers(1)
    # bind our vbo name to the GL_ARRAY_BUFFER target
    GL.glBindBuffer(GL.GL_ARRAY_BUFFER, vbo)
    # move the vertex data to a new data store associated with our vbo
    GL.glBufferData(GL.GL_ARRAY_BUFFER, ctypes.sizeof(triangle_array),
                    triangle_array, GL.GL_STATIC_DRAW)

    # vertex shader
    vertexShaderProgram = """#version 100
        in vec2 position;
        void main() {
            gl_Position = vec4(position, 0.0, 1.0);
        }"""
    vertexShader = GL.glCreateShader(GL.GL_VERTEX_SHADER)
    GL.glShaderSource(vertexShader, vertexShaderProgram)
    GL.glCompileShader(vertexShader)

    # fragment shader
    fragmentShaderProgram = """#version 100
        out vec4 outColor;
        void main() {
            outColor = vec4(1.0, 1.0, 1.0, 1.0);
        }"""

    fragmentShader = GL.glCreateShader(GL.GL_FRAGMENT_SHADER)
    GL.glShaderSource(fragmentShader, fragmentShaderProgram)
    GL.glCompileShader(fragmentShader)

    # shader program
    shaderProgram = GL.glCreateProgram()
    GL.glAttachShader(shaderProgram, vertexShader)
    GL.glAttachShader(shaderProgram, fragmentShader)

    # color output buffer assignment
    GL.glBindFragDataLocation(shaderProgram, 0, b"outColor")

    # link the program
    GL.glLinkProgram(shaderProgram)

    # validate the program
    GL.glValidateProgram(shaderProgram)

    # activate the program
    GL.glUseProgram(shaderProgram)

    # specify the layout of our vertex data
    posAttrib = GL.glGetAttribLocation(shaderProgram, b"position")
    GL.glEnableVertexAttribArray(posAttrib)
    GL.glVertexAttribPointer(posAttrib, 2, GL.GL_FLOAT, False, 0,
                             ctypes.c_voidp(0))

    # do the actual drawing
    GL.glClearColor(1.0, 0.5, 0.0, 1.0)
    GL.glClear(GL.GL_COLOR_BUFFER_BIT)
    GL.glDrawArrays(GL.GL_TRIANGLES, 0, int(len(triangle_vertices) / 2))

    # show the back buffer
    sdl2.SDL_GL_SwapWindow(window)

    # wait for somebody to close the window
    event = sdl2.SDL_Event()
    while sdl2.SDL_WaitEvent(ctypes.byref(event)):
        if event.type == sdl2.SDL_QUIT:
            break

    # cleanup
    GL.glDisableVertexAttribArray(posAttrib)
    GL.glDeleteProgram(shaderProgram)
    GL.glDeleteShader(fragmentShader)
    GL.glDeleteShader(vertexShader)
    GL.glDeleteBuffers(1, [vbo])
    GL.glDeleteVertexArrays(1, [vao])
    sdl2.SDL_GL_DeleteContext(context)
    sdl2.SDL_Quit()


if __name__ == "__main__":
    run()
