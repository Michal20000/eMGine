#pragma once
//#include<glad/glad.h> gl3w tu bedzie
#include <cstdint>
#include<string>
#include<fstream>
#include<iostream>

char* LoadShaderSource(const char* _filepath);
uint32_t CompileShader(const char* _source, GLenum _stage, const char* _msg);