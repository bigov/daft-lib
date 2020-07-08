#define GLSL(src) "#version 330\n" #src

// Vertex shader
const char* vertex_shader_text = GLSL (

  in vec2 vPos;
  in vec4 vColor;
  in vec2 vTex;

  out vec4 color;
  out vec2 tex_coord;

  void main()
  {
    gl_Position = vec4(vPos, 0.0, 1.0);
    color = vColor;
    tex_coord = vTex;
  }
);


// Fragment shader
const char* fragment_shader_text = GLSL (

  in vec4 color;
  in vec2 tex_coord;
  uniform sampler2D texture_0;

  out vec4 FragmentColor;

  void main()
  {
    vec4 tColor = texture2D(texture_0, tex_coord);
    FragmentColor = vec4(color.rgb, 1.f - tColor.r);
  }
);

