#version 460 core

//in
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;

//out
out vec4 color;

//uniform
layout(location = 0) uniform vec3 cameraPosition;
layout(location = 1) uniform mat4 modelMatrix; //same location as in vertex shader

void main()
{
	//const vec3 cameraPosition = vec3(0.1, 0.2, 5.0);
	const vec3 lightPosition = vec3(1.0, 2.0, 3.0);
	const float ambient = 0.1;

	//vec3 viewDirection = normalize(cameraPosition - inPosition);
	//vec3 lightPositionT = (modelMatrix * vec4(lightPosition, 1.0)).xyz;
	vec3 lightDirection = normalize(lightPosition - inPosition);
	float diffuse = max(dot(inNormal, lightDirection), 0.0);
	color = vec4((diffuse + ambient) * inColor, 1.0);

}