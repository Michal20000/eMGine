#pragma once
#include "EntityEngine/EntityEngine.hpp"
#include "Mesh.hpp"
#include "Material.hpp"

class MeshData : EntityFragment<MeshData>
{
	public:
	Mesh* mesh;
	Material* material;

	private:
	;
	
};