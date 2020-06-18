#define GLSL(src) "#version 330\n" #src

// Vertex shader
const char* vertex_shader_text = GLSL (

  in vec2 vPos;
  in vec4 vColor;
  uniform mat4 projection;

  out vec4 color;

  void main()
  {
    gl_Position = projection * vec4(vPos, 0.0, 1.0);
    color = vColor;
  }
);


// Fragment shader
const char* fragment_shader_text = GLSL (

  in vec4 color;

  void main()
  {
    gl_FragColor = color;
  }
);

