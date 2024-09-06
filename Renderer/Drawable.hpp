#pragma once
#include "EntityFragment.hpp"
#include "Mesh.hpp"

class Material;

class Drawable : public EntityFragment<Drawable>
{
	public:
	Drawable();
	void SetMesh(Mesh& mesh);
	Mesh& GetMesh();
	void SetMaterial(Material& material);
	Material& GetMaterial();
	;
	
	private:
	Mesh* m_Mesh;
	Material* m_Material;
	;
	
};

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
