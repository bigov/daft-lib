#version 330
//
// GLSL vertex shader
//
in vec3 C3df;
in vec3 Ramp;
in float Type;
in float Side;
in float Gage;

out vec3 vRamp;
out float vType;
out float vSide;
out float vGage;

void main()
{
	vRamp = Ramp;
	vType = Type;
	vSide = Side;
	vGage = Gage;

	gl_Position = vec4(C3df, 1.0);
}

