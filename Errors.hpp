#pragma once
#include <cstdint>
#include <stdexcept>



#define THROW(Expression, ErrorClass, Error) if (Expression) [[unlikely]] throw ErrorClass(Error)
#ifdef DEBUG
#define DEBUG_THROW(Expression, ErrorClass, Error) THROW(Expression, ErrorClass, Error)
#else
#define DEBUG_THROW(Expression, ErrorClass, Error)
#endif
#ifdef RELEASE
#define RELEASE_THROW(Expression, ErrorClass, Error) THROW(Expression, ErrorClass, Error)
#else
#define RELEASE_THROW(Expression, ErrorClass, Error)
#endif



class GLError : public std::runtime_error
{
	public:
	GLError(const char* error);

};
class GLFWError : public std::runtime_error
{
	public:
	GLFWError(const char* error);

};
