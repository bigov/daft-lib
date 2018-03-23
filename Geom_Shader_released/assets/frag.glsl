#version 330
//
// GLSL fragments shader
//

in vec2 f_texcoord;
in vec4 f_bright;

out vec4 FragColor;
uniform sampler2D texture_0;

void main(void)
{
  vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0 - f_texcoord.y);

	if (gl_FrontFacing)
	{
  	FragColor = texture2D(texture_0, flipped_texcoord) + f_bright;
	} else
	{
  	FragColor = texture2D(texture_0, flipped_texcoord) + f_bright * vec4(0.15)
		- vec4(0.75, 0.75, 0.5, 0.0);
	}

}
// Если использовать отрисовку обратных сторон проверхности - параметр
//
//		gl::Disable(gl::CULL_FACE);
//
// в настройке OpenGL. То можно, например, имитировать погружение в объем
// жидкости, понизив контрастность освещения [ f_bright * vec4(0.15) ], и
// уменьшив яркость света [ -vec4(0.75, 0.75, 0.5, 0.0) ] со смещением
// в сторону синего цвета при отрисовки пикселей на обратных поверхностях:
//
//	if (gl_FrontFacing)
//	{
//  	FragColor = texture2D(texture_0, flipped_texcoord) + f_bright;
//	}
//	else
//	{
//  	FragColor = texture2D(texture_0, flipped_texcoord) 
//				+ f_bright * vec4(0.15) - vec4(0.75, 0.75, 0.5, 0.0);
//	}
//
// Текстуры для сторон водяного куба надо
//		- копировать из текстур соседних элементов, если это не вода
//		- не отображать, если сосдений элемент тоже вода;
//		- рисовать прозрачную пленку сверху на границе с воздухом.
//
