#version 460 core

//in
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;

//out
layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out vec3 outColor;

out gl_PerVertex
{
	vec4 gl_Position;
};

//uniform
layout(location = 0) uniform mat4 mvpMatrix;
layout(location = 1) uniform mat4 modelMatrix;
layout(location = 2) uniform mat3 normalMatrix;

void main()
{
	outColor = inColor;
	outNormal = normalize(normalMatrix * inNormal);
	outPosition = (modelMatrix * vec4(inPosition, 1.0)).xyz;
	gl_Position = mvpMatrix * vec4(inPosition, 1.0);

}