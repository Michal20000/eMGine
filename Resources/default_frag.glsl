#version 460 core

layout(location = 0) in vec2 inColor;
out vec4 outColor;

void main()
{
	outColor = inColor;
}