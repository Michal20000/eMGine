#include "Renderer.hpp"



Renderer::Renderer(Application& application) :
	m_Application(application)
{
}
Renderer::~Renderer()
{
}



Application& Renderer::GetApplication()
{
	return m_Application;
	
}
