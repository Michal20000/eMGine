#include "Drawable.hpp"

#include "Mesh.hpp"

Drawable::Drawable() :
	m_Mesh(nullptr),
	m_Material(nullptr)
{}

void Drawable::SetMesh(Mesh& mesh)
{
	m_Mesh = &mesh;
}

Mesh& Drawable::GetMesh()
{
	if (m_Mesh == nullptr)
		LOG_WARN("Mesh pointer in Drawable is null");

	return *m_Mesh;

}

void Drawable::SetMaterial(Material& material)
{
	m_Material = &material;
}

Material& Drawable::GetMaterial()
{
	if (m_Material == nullptr)
		LOG_WARN("Material pointer in Drawable is null");

	return *m_Material;
}

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
