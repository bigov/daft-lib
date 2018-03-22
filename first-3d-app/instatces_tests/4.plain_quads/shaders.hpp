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

	in vec4 pos3d;
	in vec4 color;
	in vec4 normal;
	in vec2 tex2d;

	uniform mat4 mvp;
	out vec4 vColor;
	out vec2 vTex2d;

	vec4 origin = vec4(0.1, 0.1, 0.1, 0.0);

	void main()
	{
		vec4 l_direct = vec4(0.1, 0.1, 0.1, 0.0);
		vec4 bright = vec4(dot(l_direct, normal));
		vColor = (color + bright) * vec4(0.3);
		vTex2d = tex2d;

		gl_Position = mvp * (pos3d + origin);
	}
);

//### Код геометрического шейдера
//const GLchar * geom_shader = GLSL (
//
//    in vec3 vColor[];
//    out vec3 fColor;
//
//    void main()
//    {
//        fColor = vColor[0];
//    } 
//);

//### Код фрагментного шейдера
const GLchar * frag_shader = GLSL(

	in vec4 vColor;
	in vec2 vTex2d;

	uniform sampler2D texture_0;

  out vec4 outColor;

  void main()
  {
		vec2 flip_tex = vec2(vTex2d.x, 1.0 - vTex2d.y);
  	outColor = vColor + texture2D(texture_0, flip_tex);
  }
);

