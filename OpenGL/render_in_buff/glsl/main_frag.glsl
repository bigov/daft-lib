#version 330

in vec3 FrColor;
uniform uint Xid;

layout(location = 0) out vec3  OutColor;
layout(location = 1) out uvec3 FragData;

void main()
{
  OutColor = FrColor;
  FragData = uvec3(Xid, 0, 0);
}
