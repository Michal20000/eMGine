#pragma once
#include <glm.hpp>

class Shader;

class Material
{
	public:
	Shader* ShaderPtr()
	{
		return m_Shader;
	}

	private:
	Shader* m_Shader;
	glm::vec4 m_Color;

};

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
