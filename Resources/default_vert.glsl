#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inColor;
layout(location = 0) uniform mat4 mvpMatrix;
layout(location = 0) out vec2 outColor;

out gl_PerVertex
{
	vec4 gl_Position;
};

void main()
{
	//vertexColor = inColor;
	outColor = inColor;
	gl_Position = mvpMatrix * vec4(inPosition, 1.0);
}