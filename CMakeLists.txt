set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.10)
project(Hello)

# set(CMAKE_C_FLAGS "")
# set(CMAKE_C_FLAGS_DEBUG "-DDEBUG -g")
# set(CMAKE_C_FLAGS_RELEASE "-DRELEASE -O3")

# set(CMAKE_CXX_FLAGS "")s
# set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -g")
# set(CMAKE_CXX_FLAGS_RELEASE "-DRELEASE -O3")

# set(CMAKE_EXE_LINKER_FLAGS)
# set(CMAKE_EXE_LINKER_FLAGS_DEBUG)
# set(CMAKE_EXE_LINKER_FLAGS_RELEASE)

# target_compile_options(M0 -Wall -Wextra -Werror)
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TARGET := project_0_DEBUG
# TARGET := project_0_RELEASE
# TARGET := project_1_DEBUG
# TARGET := project_1_RELEASE

# eMGine
# 	eMGine_cpps
# 	eMGine_hpps
# 	eMGine
# 	Libraries
# 	Build
# 	Binaries
# 	Benchmarks
# 	CMake trash...

# mainlib
#	runtime_0 runtime_1 runtime_2...
# test_0 test_1 test_2...

set(ALL_FLAGS, "-DALL=1")
set(DEBUG_FLAGS "-DDEBUG=1 -O0 -g")
set(RELEASE_FLAGS "-DRELEASE=1 -O3")

add_executable(Hello_DEBUG Main.cpp Memory.cpp BitField.hpp Timer.cpp EntityEngine/EntityContainer.cpp EntityEngine/EntityEngine.cpp EntityEngine/EntityTable.cpp EntityEngine/EntityView.cpp)
set_target_properties(Hello_DEBUG PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../Binaries/Hello/Debug")
target_compile_options(Hello_DEBUG PUBLIC ${ALL_FLAGS} ${DEBUG_FLAGS})
target_include_directories(Hello_DEBUG PRIVATE ".")
target_include_directories(Hello_DEBUG PRIVATE "./EntityEngine")
# TODO: flags for compiler

# EntityEngine/EntityContainer.cpp
add_executable(Hello_RELEASE Main.cpp Memory.cpp BitField.hpp Timer.cpp EntityEngine/EntityContainer.cpp EntityEngine/EntityEngine.cpp EntityEngine/EntityTable.cpp EntityEngine/EntityView.cpp)
set_target_properties(Hello_RELEASE PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../Binaries/Hello/Release")
target_compile_options(Hello_RELEASE PUBLIC ${ALL_FLAGS} ${RELEASE_FLAGS})
target_include_directories(Hello_RELEASE PRIVATE ".")
target_include_directories(Hello_RELEASE PRIVATE "./EntityEngine")
# TODO: flags for compiler
