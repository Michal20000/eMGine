#include "Drawable.hpp"

void Drawable::SetMesh(Mesh& mesh)
{
	m_Mesh = &mesh;
}

Mesh& Drawable::GetMesh()
{
	return *m_Mesh;
}

void Drawable::SetMaterial(Material& material)
{
	m_Material = &material;
}

Material& Drawable::GetMaterial()
{
	return *m_Material;
}

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
