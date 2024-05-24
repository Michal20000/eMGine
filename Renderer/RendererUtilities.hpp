#pragma once
#include <cstdint>

#include "Dependencies/glm/glm.hpp"
// #include "Buffer.hpp"
// #include "Vector.hpp"
// #include "BitField.hpp"
#include "EntityEngine/EntityEngine.hpp"
#include "Logs.hpp"
#include "Errors.hpp"



#define BLENGTH(X) sizeof(X)
#define DEFAULT_5_RULE(Class) Class() = default; Class(const Class& ob) = default; Class(Class&& ob) = default; ~Class() = default; Class& operator=(const Class& ob) = default; Class& operator=(Class&& ob) = default
#define STRINGIFY_BUFFER(X) #X
#define STRINGIFY(X) STRINGIFY_BUFFER(X)

#ifdef DEBUG
#define GL(Function) Function; do { uint32_t error = glGetError(); if (error != 0) LOG_FL_ERROR("GL Error " << error); } while (false)
#else
#define GL(Function) Function
#endif

#ifdef DEBUG
#define GLFW(Function) Function; do { const char* description; int32_t error = glfwGetError(&description); if (error != 0) LOG_FL_ERROR("GLFW Error " << error << " " << description); } while (false)
#else
#define GLFW(Function) Function
#endif

// Deklaracja wskaznikow i typow;
class GLFWwindow;
class GLFWmonitor;
class GLFWcursor;


// Struktury prymitywne;
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    //glm::vec2 uv;
    
};

struct Mesh
{
    uint32_t vertexArray;
    uint32_t vertexBuffer;
    uint32_t indexBuffer;
    //texture;
    size_t indexCount;

};