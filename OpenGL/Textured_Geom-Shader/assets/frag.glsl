#version 330

in vec4 fColor;
in vec2 f_texcoord;
flat in int enable;
uniform sampler2D texture_0;

out vec4 outColor;

void main()
{
  if(enable == 0) discard;
  vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0 - f_texcoord.y);
  outColor = texture2D(texture_0, flipped_texcoord);

  //outColor = texture2D(texture_0, f_texcoord) + 0.5 * fColor;
  //outColor = fColor;
}

