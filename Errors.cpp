#include "Errors.hpp"
#include <string>



GLError::GLError(const char* error) :
	std::runtime_error(error)
{
}
GLFWError::GLFWError(const char* error) :
	std::runtime_error(error)
{
}
