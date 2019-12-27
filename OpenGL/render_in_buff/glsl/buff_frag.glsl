#version 330

in vec2 Texcoord;
uniform sampler2D texFramebuffer;

out vec4 FragColor;

void main(void)
{
  FragColor = texture(texFramebuffer, Texcoord);
}
