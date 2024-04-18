#pragma once
#include <iostream>



#define STRINGIFY_BUFFER(X) #X
#define STRINGIFY(X) STRINGIFY_BUFFER(X)
#define FL __FILE__ ":" STRINGIFY(__LINE__) " "

#define LF "\n"
#define CRLF "\r\n"
#define RED "\u001b[31m"
#define YELLOW "\u001b[33m"
#define BLUE "\u001b[34m"
#define GREEN "\u001b[32m"
#define PURPLE "\u001b[36m"
#define DEFAULT "\u001b[0m"



#define LOG_ERROR(X) std::cout << RED << X << LF DEFAULT
#define LOG_FL_ERROR(X) std::cout << RED FL << X << LF DEFAULT
#define ECHO_ERROR(X) std::cout << RED #X " = " << X << LF DEFAULT
#define ECHO_FL_ERROR(X) std::cout << RED FL #X " = " << X << LF DEFAULT

#define LOG_WARN(X) std::cout << YELLOW << X << LF DEFAULT
#define LOG_FL_WARN(X) std::cout << YELLOW FL << X << LF DEFAULT
#define ECHO_WARN(X) std::cout << YELLOW #X " = " << X << LF DEFAULT
#define ECHO_FL_WARN(X) std::cout << YELLOW FL #X " = " << X << LF DEFAULT

#define LOG(X) std::cout << X << LF
#define LOG_FL(X) std::cout << FL << X << LF
#define ECHO(X) std::cout << #X " = " << X << LF
#define ECHO_FL(X) std::cout << FL #X " = " << X << LF

#define LOG_DEBUG(X) std::cout << BLUE << X << LF DEFAULT
#define LOG_FL_DEBUG(X) std::cout << BLUE FL << X << LF DEFAULT
#define ECHO_DEBUG(X) std::cout << BLUE #X " = " << X << LF DEFAULT
#define ECHO_FL_DEBUG(X) std::cout << BLUE FL #X " = " << X << LF DEFAULT

#define LOG_VERBOSE(X) std::cout << GREEN << X << LF DEFAULT
#define LOG_FL_VERBOSE(X) std::cout << GREEN FL << X << LF DEFAULT
#define ECHO_VERBOSE(X) std::cout << GREEN #X " = " << X << LF DEFAULT
#define ECHO_FL_VERBOSE(X) std::cout << GREEN FL #X " = " << X << LF DEFAULT

#define LOG_SILLY(X) std::cout << PURPLE << X << LF DEFAULT
#define LOG_FL_SILLY(X) std::cout << PURPLE FL << X << LF DEFAULT
#define ECHO_SILLY(X) std::cout << PURPLE #X " = " << X << LF DEFAULT
#define ECHO_FL_SILLY(X) std::cout << PURPLE FL #X " = " << X << LF DEFAULT
