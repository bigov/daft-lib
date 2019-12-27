#version 330

in vec2 VertexPosition;
in vec2 TextureCoord;

out vec2 Texcoord;

void main(void)
{
  Texcoord = TextureCoord;
  gl_Position = vec4(VertexPosition, 0.0, 1.0);
}

