#version 330
//
// GLSL geometric shader
//

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

in vec3 vRamp[];
in float vType[];
in float vSide[];
in float vGage[];
uniform mat4 mvp;
uniform vec3 ViewFrom;

out vec4 f_bright;
out vec2 f_texcoord;

vec4 l_direct = normalize(mvp * vec4(0.3, 0.6, -0.5, 0.0));
vec4 l_bright = vec4(0.16, 0.16, 0.20, 0.0);
vec4 P = mvp * gl_in[0].gl_Position;

vec4 LookDir = normalize(gl_in[0].gl_Position - vec4(ViewFrom, 1.0));

////  Описание структуры gl_in[]:
//
// in gl_PerVertex
// {
//    vec4 gl_Position;
//    float gl_PointSize;
//    float gl_ClipDistance[];
// } gl_in[];
//
// Where
// gl_PointSize — contains size of rasterized points, in pixels
// gl_ClipDistance — provides mechanism for vertex clipping


void paint(vec4 v)
{
	gl_Position = P + v;
  EmitVertex();
	return;
}

void main(void)
{
	// Координаты текстурной карты
	float u0 = (vType[0] - 1.0) * 0.125;
	float u1 = u0 + 0.125;

	float v0 = 0,	v1 = v0 + 0.125,
		v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;

	if (vType[0] == 1.0) 
	{
		v2  = v0;
		v3  = v1;
		v4  = v0;
		v5  = v1;
		v6  = v0;
		v7  = v1;
		v8  = v0;
		v9  = v1;
		v10 = v0;
		v11 = v1;
	} else {
		v2  = v1;
		v3  = v1 + 0.125;
		v4  = v3;
		v5  = v3 + 0.125;
		v6  = v5;
		v7  = v5 + 0.125;
		v8  = v7;
		v9  = v7 + 0.125;
		v10 = v9;
		v11 = v9 + 0.125;
	}


	// Данные для управления отображением сторон элемента
	float si = vSide[0];
	
	bool pX = true, nX = true, pY = true, nY = true, pZ = true, nZ = true;
	float d_si;
	
	d_si = si/10;
	si = floor(d_si);
	if (d_si == si) pX = false;
	
	d_si = si/10;
	si = floor(d_si);
	if (d_si == si) nX = false;
	
	d_si = si/10;
	si = floor(d_si);
	if (d_si == si) pY = false;
	
	d_si = si/10;
	si = floor(d_si);
	if (d_si == si) nY = false;
	
	d_si = si/10;
	si = floor(d_si);
	if (d_si == si) pZ = false;
	
	d_si = si/10;
	si = floor(d_si);
	if (d_si == si) nZ = false;

	// Размер(масштаб) стороны элемента
	float s = 0.5 * vGage[0];

	// поворот на оси X
	mat4 mvpR = mvp * mat4(
		1,               0,                0, 0,
		0, cos(vRamp[0].x), -sin(vRamp[0].x), 0,
    0, sin(vRamp[0].x),  cos(vRamp[0].x), 0, 
		0,               0,                0, 1
	);

	// поворот на оси Y
	mvpR = mvpR * mat4(
		cos(vRamp[0].y),  0, -sin(vRamp[0].y),  0,
		              0,  1,                0,  0,
		sin(vRamp[0].y),  0,  cos(vRamp[0].y),  0, 
			            0,  0,                0,  1
	);

	// поворот на оси Z
	mvpR = mvpR * mat4(
		cos(vRamp[0].z), -sin(vRamp[0].z),  0,  0,
		sin(vRamp[0].z),  cos(vRamp[0].z),  0,  0, 
		              0,  0,                1,  0,
			            0,  0,                0,  1
	);


//    pY
//    | 
//    |_____ pX
//    / 
//   /pZ
//
//     7(-+-)~~~~~~~~2(++-)
//    /|            /|   
//   / |           / |
//  6(-++)~~~~~~~~3(+++)
//  |  |          |  |
//  |  |          |  |
//  |  4(---)~~~~~|~~1(+--)
//  | /           | /
//  |/            |/mvp * 
//  5(--+)~~~~~~~~0(+-+)

  // векторы смещения от ценральной точки для получения координт 8 вершин куба
	vec4 p0 = mvpR * vec4( s, -s,  s, 0.0);
  vec4 p1 = mvpR * vec4( s, -s, -s, 0.0);
  vec4 p2 = mvpR * vec4( s,  s, -s, 0.0);
  vec4 p3 = mvpR * vec4( s,  s,  s, 0.0);
  vec4 p4 = mvpR * vec4(-s, -s, -s, 0.0);
  vec4 p5 = mvpR * vec4(-s, -s,  s, 0.0);
  vec4 p6 = mvpR * vec4(-s,  s,  s, 0.0);
  vec4 p7 = mvpR * vec4(-s,  s, -s, 0.0);

	// векторы нормалей к граням
	vec4 NpX = normalize(mvpR * vec4( 1.0,  0.0,  0.0,  0.0));
	vec4 NnX = normalize(mvpR * vec4(-1.0,  0.0,  0.0,  0.0));
	vec4 NpY = normalize(mvpR * vec4( 0.0,  1.0,  0.0,  0.0));
	vec4 NnY = normalize(mvpR * vec4( 0.0, -1.0,  0.0,  0.0));
	vec4 NpZ = normalize(mvpR * vec4( 0.0,  0.0,  1.0,  0.0));
	vec4 NnZ = normalize(mvpR * vec4( 0.0,  0.0, -1.0,  0.0));

	if( dot(NpX, normalize(mvp * LookDir)) > 0.) pX = false;
	if( dot(NnX, normalize(mvp * LookDir)) > 0.) nX = false;
	if( dot(NpY, normalize(mvp * LookDir)) > 0.) pY = false;
	if( dot(NnY, normalize(mvp * LookDir)) > 0.) nY = false;
	if( dot(NpZ, normalize(mvp * LookDir)) > 0.) pZ = false;
	if( dot(NnZ, normalize(mvp * LookDir)) > 0.) nZ = false;

	if (pX) {
	f_bright = vec4(dot(l_direct, NpX)) * l_bright;

	f_texcoord = vec2(u0, v0);
  paint(p0);
	f_texcoord = vec2(u1, v0);
  paint(p1);
	f_texcoord = vec2(u0, v1);
  paint(p3);
 	f_texcoord = vec2(u1, v1);
  paint(p2);
	EndPrimitive();
	}

	if (nX) {
	f_bright = vec4(dot(l_direct, NnX)) * l_bright;

	f_texcoord = vec2(u0, v2);
  paint(p4);
	f_texcoord = vec2(u1, v2);
  paint(p5);
	f_texcoord = vec2(u0, v3);
  paint(p7);
	f_texcoord = vec2(u1, v3);
  paint(p6);
	EndPrimitive();
	}

	if (pY) {
	f_bright = vec4(dot(l_direct, NpY)) * l_bright;

	f_texcoord = vec2(u0, v4);
  paint(p6);
  f_texcoord = vec2(u1, v4);
  paint(p3);
  f_texcoord = vec2(u0, v5);
  paint(p7);
  f_texcoord = vec2(u1, v5);
  paint(p2);
	EndPrimitive();
	}
   
	if (nY) {
	f_bright = vec4(dot(l_direct, NnY)) * l_bright;

	f_texcoord = vec2(u0, v6);
  paint(p4);
	f_texcoord = vec2(u1, v6);
  paint(p1);
	f_texcoord = vec2(u0, v7);
  paint(p5);
	f_texcoord = vec2(u1, v7);
  paint(p0);
	EndPrimitive();
	}

	if (pZ) {
	f_bright = vec4(dot(l_direct, NpZ)) * l_bright;

	f_texcoord = vec2(u0, v8);
  paint(p5);
  f_texcoord = vec2(u1, v8);
  paint(p0);
  f_texcoord = vec2(u0, v9);
  paint(p6);
  f_texcoord = vec2(u1, v9);
  paint(p3);
	EndPrimitive();
	}

	if (nZ) {
	f_bright = vec4(dot(l_direct, NnZ)) * l_bright;

	f_texcoord = vec2(u0, v10);
  paint(p1);
	f_texcoord = vec2(u1, v10);
  paint(p4);
	f_texcoord = vec2(u0, v11);
  paint(p2);
	f_texcoord = vec2(u1, v11);
  paint(p7);
	EndPrimitive();
	}
}
