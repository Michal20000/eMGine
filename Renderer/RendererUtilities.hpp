#pragma once
#include <cstdint>

// #include "Buffer.hpp"
// #include "Vector.hpp"
// #include "BitField.hpp"
#include "Logs.hpp"
#include "Errors.hpp"



#define BLENGTH(X) sizeof(X)
#define DEFAULT_5_RULE(Class) Class() = default; Class(const Class& ob) = default; Class(Class&& ob) = default; ~Class() = default; Class& operator=(const Class& ob) = default; Class& operator=(Class&& ob) = default
#define STRINGIFY_BUFFER(X) #X
#define STRINGIFY(X) STRINGIFY_BUFFER(X)

// Deklaracja wskaznikow i typow;



// Struktury prymitywne;
