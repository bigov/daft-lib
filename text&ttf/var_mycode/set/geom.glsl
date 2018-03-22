//----------------------------------------------------------------------------
//
// file: geom.glsl
//
//### Код геометрического шейдера
//
//----------------------------------------------------------------------------
#version 330

layout(points) in;
layout(line_strip, max_vertices = 16) out;

in vec3 vColor[];
out vec3 fColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
        fColor = vColor[0];

        // +X direction is "North", -X direction is "South"
        // +Y direction is "Up",    -Y direction is "Down"
        // +Z direction is "East",  -Z direction is "West"
        //                                     N/S   U/D   E/W
        vec4 NEU = proj * view * model * vec4( 0.1,  0.1,  0.1, 0.0);
        vec4 NED = proj * view * model * vec4( 0.1, -0.1,  0.1, 0.0);
        vec4 NWU = proj * view * model * vec4( 0.1,  0.1, -0.1, 0.0);
        vec4 NWD = proj * view * model * vec4( 0.1, -0.1, -0.1, 0.0);
        vec4 SEU = proj * view * model * vec4(-0.1,  0.1,  0.1, 0.0);
        vec4 SED = proj * view * model * vec4(-0.1, -0.1,  0.1, 0.0);
        vec4 SWU = proj * view * model * vec4(-0.1,  0.1, -0.1, 0.0);
        vec4 SWD = proj * view * model * vec4(-0.1, -0.1, -0.1, 0.0);

				mat4 PVM;
				PVM = mat4(1); // <- если оставить это значение, то будут нарисованы
				               // 4 куба, вращающиеся каждый вокруг своей оси
				PVM = proj * view * model;

        // Create a cube centered on the given point.
        gl_Position = PVM * gl_in[0].gl_Position + NED;
				fColor = vColor[0] * vec3(0.5, 0.5, 0.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NWD;
				fColor = vColor[0] * vec3(0.5, 0.5, 0.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SWD;
				fColor = vColor[0] * vec3(0.5, 0.5, 0.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SED;
				fColor = vColor[0] * vec3(0.5, 0.5, 0.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SEU;
				fColor = vColor[0] * vec3(1.5, 1.5, 1.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SWU;
				fColor = vColor[0] * vec3(1.5, 1.5, 1.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NWU;
				fColor = vColor[0] * vec3(1.5, 1.5, 1.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NEU;
				fColor = vColor[0] * vec3(1.5, 1.5, 1.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NED;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SED;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SEU;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NEU;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NWU;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NWD;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SWD;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SWU;
        EmitVertex();

        EndPrimitive();
}
