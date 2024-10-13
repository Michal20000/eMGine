#pragma once
#include "EntityFragment.hpp"

class Mesh;
class Material;

class Drawable : public EntityFragment<Drawable>
{
	public:
	Drawable();

	void SetMesh(Mesh& mesh);
	Mesh& GetMesh();
	void SetMaterial(Material& material);
	Material& GetMaterial();
	
	private:
	Mesh* m_Mesh;
	Material* m_Material;
	
};

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
