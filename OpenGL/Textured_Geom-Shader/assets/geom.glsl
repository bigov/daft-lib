#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 26) out;
uniform mat4 MVP;

out vec4 fColor;
flat out int enable;
out vec2 f_texcoord;

vec4 P = MVP * gl_in[0].gl_Position;

void paint(vec4 v)
{
  gl_Position = P + v;
  EmitVertex();
  return;
};

void main()
{
  enable = 1;
  f_texcoord = vec2(0.0, 0.25);

  // координты вершин куба
  vec4 p0 = MVP * vec4( 0.2, -0.2,  0.2, 0.0);
  vec4 p1 = MVP * vec4( 0.2, -0.2, -0.2, 0.0);
  vec4 p2 = MVP * vec4( 0.2,  0.2, -0.2, 0.0);
  vec4 p3 = MVP * vec4( 0.2,  0.2,  0.2, 0.0);
  vec4 p4 = MVP * vec4(-0.2, -0.2,  0.2, 0.0);
  vec4 p5 = MVP * vec4(-0.2, -0.2, -0.2, 0.0);
  vec4 p6 = MVP * vec4(-0.2,  0.2, -0.2, 0.0);
  vec4 p7 = MVP * vec4(-0.2,  0.2,  0.2, 0.0);

  // для построения куба порядок обхода вершин
  // против часовой стрелки: 0,1,3,2,6,1,5,0,4,3,7,6,4,5
  // или по часовой стрелке: 3,0,7,4,5,0,1,3,2,7,6,5,2,1

  // pX
  fColor = vec4(0.0, 0.0, 0.0, 1.0);
  f_texcoord = vec2(0.125, 0.0);
   paint(p0);
  f_texcoord = vec2(0.25, 0.0);
  paint(p1);
  f_texcoord = vec2(0.125, 0.125);
  paint(p3);
  f_texcoord = vec2(0.25, 0.125);
   paint(p2);

  // pY
  fColor = vec4(1.0, 0.0, 0.0, 0.8);
  f_texcoord = vec2(0.125, 0.25);
  paint(p2);
  f_texcoord = vec2(0.25, 0.25);
  paint(p6);
  f_texcoord = vec2(0.125, 0.375);
  paint(p3);
  f_texcoord = vec2(0.25, 0.375);
  paint(p7);

  // pZ
  fColor = vec4(0.0, 1.0, 1.0, 0.8);
  f_texcoord = vec2(0.125, 0.500);
  paint(p7);
  f_texcoord = vec2(0.25, 0.500);
  paint(p4);
  f_texcoord = vec2(0.125, 0.625);
  paint(p3);
  f_texcoord = vec2(0.25, 0.625);
  paint(p0);

  // discard
  enable = 0; paint(p4); enable = 1;

  // nY
  fColor = vec4(0.0, 0.0, 1.0, 0.8);
  f_texcoord = vec2(0.125, 0.375);
  paint(p4);
  f_texcoord = vec2(0.25, 0.375);
  paint(p5);
  f_texcoord = vec2(0.125, 0.500);
  paint(p0);
  f_texcoord = vec2(0.25, 0.500);
  paint(p1);

  // nZ
  fColor = vec4(1.0, 0.0, 1.0, 0.8);
  f_texcoord = vec2(0.125, 0.625);
  paint(p1);
  f_texcoord = vec2(0.25, 0.625);
  paint(p5);
  f_texcoord = vec2(0.125, 0.750);
  paint(p2);
  f_texcoord = vec2(0.25, 0.750);
  paint(p6);

  // nX
  fColor = vec4(1.0, 1.0, 0.0, 0.8);
  f_texcoord = vec2(0.125, 0.125);
  paint(p6);
  f_texcoord = vec2(0.25, 0.125);
  paint(p5);
  f_texcoord = vec2(0.125, 0.25);
  paint(p7);
  f_texcoord = vec2(0.25, 0.25);
  paint(p4);

  EndPrimitive();
}

