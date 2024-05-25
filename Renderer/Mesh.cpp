#include "Dependencies/GL3W/include/gl3w.h"
#include "Mesh.hpp"

void Mesh::LoadFromProgram(glm::vec3 positions[], glm::vec3 normals[], glm::vec3 colors[])
{
	if (positions == nullptr || normals == nullptr)
	{
		LOG_ERROR("Invalid mesh data to import");
		return;

	}

	vertexBuffer = vertexArray.VertexBuffer();
	indexBuffer = vertexArray.IndexBuffer();

	if (colors == nullptr)
	{
		vertexArray.AddAttribute(3, 6*sizeof(float), GL_FLOAT, 0, false); //position
		vertexArray.AddAttribute(3, 6*sizeof(float), GL_FLOAT, 3*sizeof(float), true); //normals

	}

	else
	{
		vertexArray.AddAttribute(3, 9*sizeof(float), GL_FLOAT, 0, false); //position
		vertexArray.AddAttribute(3, 9*sizeof(float), GL_FLOAT, 3*sizeof(float), true); //normals
		vertexArray.AddAttribute(3, 9*sizeof(float), GL_FLOAT, 6*sizeof(float), false); //color/uvw

	}

	//...
	;

}