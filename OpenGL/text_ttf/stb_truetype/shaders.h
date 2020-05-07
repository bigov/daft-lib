/*
 *
 * Shaders content
 *
 */
#define GLSL(src) "#version 330\n" #src

const char* vertex_shader_text = GLSL (

  in vec2 vPos;
  in vec2 texture_2dcoord;
  uniform mat4 MVP;

  out vec2 texture_coord;

  void main()
  {
    gl_Position = MVP * vec4(vPos, 0.0, 1.0);
    texture_coord = texture_2dcoord;
  }
);


const char* fragment_shader_text = GLSL (

  in vec2 texture_coord;
  uniform sampler2D texture_data;

  void main()
  {
    gl_FragColor = texture(texture_data, texture_coord);
  }
);

