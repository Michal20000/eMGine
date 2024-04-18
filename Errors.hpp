#pragma once
#include <stdexcept>



#define THROW(Expression, ErrorClass, Error) if (Expression) [[unlikely]] throw ErrorClass(Error)
#ifdef DEBUG
#define DEBUG_THROW(Expression, ErrorClass, Error) if (Expression) [[unlikely]] throw ErrorClass(Error)
#else
#define DEBUG_THROW(Expression, ErrorClass, Error)
#endif
#ifdef RELEASE
#define RELEASE_THROW(Expression, ErrorClass, Error) if (Expression) [[unlikely]] throw ErrorClass(Error)
#else
#define RELEASE_THROW(Expression, ErrorClass, Error)
#endif
