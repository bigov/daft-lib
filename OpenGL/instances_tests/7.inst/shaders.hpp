//----------------------------------------------------------------------------
//
// file: shaders.hpp
//
// Тестовые шейдеры
//
//----------------------------------------------------------------------------

#define GLSL(src) "#version 330\n" #src

//### Код вершинного шейдера
const GLchar * vert_shader = GLSL(

	in vec3 pos3d;
	in vec3 origin;
	in vec3 color;
	in vec3 normal;
	in vec2 tex2d;

	uniform mat4 mvp;
	out vec3 vColor;
	out vec2 vTex2d;

  void main()
  {
		vec3 l_direct = vec3(0.1, 0.1, 0.1);
		vec3 bright = vec3(dot(l_direct, normal));
		vColor = (color + bright) * vec3(0.3);
		vTex2d = tex2d;

    gl_Position = mvp * (vec4(pos3d, 1.0) + vec4(origin, 0.0));
  }
);

//### Код фрагментного шейдера
const GLchar * frag_shader = GLSL(

	in vec3 vColor;
	in vec2 vTex2d;

	uniform sampler2D texture_0;

  out vec4 outColor;

  void main()
  {
		vec2 flip_tex = vec2(vTex2d.x, 1.0 - vTex2d.y);
  	outColor = vec4(vColor, 1.0) + texture2D(texture_0, flip_tex);
  }
);

