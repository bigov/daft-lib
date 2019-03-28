#version 330

in vec3 FrColor;
uniform uint Index;

layout(location = 0) out vec3  OutColor;
layout(location = 1) out uint  IdData;

void main()
{
  OutColor = FrColor;
  IdData = Index;
}
