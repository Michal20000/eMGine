#pragma once
#include "Shader.hpp"

class Material
{
	public:
	Shader* ShaderPtr()
	{
		return m_Shader;
	}

	private:
	Shader* m_Shader;

};