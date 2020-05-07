//----------------------------------------------------------------------------
//
// file: vert.glsl
//
//### Код вершинного шейдера
//
//----------------------------------------------------------------------------
#version 330

in vec2 vertex_position;
in vec2 texure_position;
out vec2 texture_points;

void main()
{
	texture_points = vec2(texure_position.x, 1.0 - texure_position.y); 
	gl_Position = vec4(vertex_position, 0.0, 1.0);
}
