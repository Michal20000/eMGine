#pragma once
//#include<glad/glad.h> gl3w tu bedzie
#include <cstdint>
#include<string>
#include<fstream>
#include<iostream>

std::string LoadShaderSource(std::string);
uint32_t CompileShader(const char* source, GLenum stage, const std::string& message);