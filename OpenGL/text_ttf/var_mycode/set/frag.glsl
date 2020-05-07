//----------------------------------------------------------------------------
//
// file: frag.glsl
//
//### Код фрагментного шейдера
//
//----------------------------------------------------------------------------
#version 330

in vec2 texture_points;
uniform sampler2D image0;
out vec4 fColor;

void main()
{
	fColor = texture(image0, texture_points);
}

