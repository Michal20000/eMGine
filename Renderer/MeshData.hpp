#pragma once
#include "EntityEngine/EntityEngine.hpp"
#include "Mesh.hpp"

class MeshData : EntityFragment<MeshData>
{
	public:
	Mesh* mesh;

	private:
	;
};