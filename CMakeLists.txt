set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.10)
project(eMGine)

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

set(ALL_FLAGS "-DALL=1")
set(DEBUG_FLAGS "-DDEBUG=1 -O0 -g")
set(RELEASE_FLAGS "-DRELEASE=1 -O3")

file(GLOB CPP_FILES "./*.cpp")
file(GLOB CONTAINERS_CPP_FILES "./Containers/*.cpp")
file(GLOB EE_CPP_FILES "./EntityEngine/*.cpp")
file(GLOB RENDERER_CPP_FILES "./Renderer/*.cpp")
file(GLOB UTILITIES_CPP_FILES "./Utilities/*.cpp")
file(GLOB MATH_CPP_FILES "./Utilities/Math/*.cpp")
set(ALL_CPP_FILES ${CPP_FILES} ${CONTAINERS_CPP_FILES} ${EE_CPP_FILES} ${RENDERER_CPP_FILES} ${UTILITIES_CPP_FILES} ${MATH_CPP_FILES} "./Dependencies/GL3W/gl3w.cpp")



add_executable(application_debug ${ALL_CPP_FILES})
set_target_properties(application_debug PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../Binaries/Debug")
target_compile_options(application_debug PUBLIC ${ALL_FLAGS} ${DEBUG_FLAGS})

target_include_directories(application_debug PRIVATE ".")
target_include_directories(application_debug PRIVATE "./Containers")
target_include_directories(application_debug PRIVATE "./EntityEngine")
target_include_directories(application_debug PRIVATE "./Renderer")
target_include_directories(application_debug PRIVATE "./Utilities")
target_include_directories(application_debug PRIVATE "./Utilities/Math")

target_include_directories(application_debug PRIVATE "./Dependencies/GLFW/include")
target_include_directories(application_debug PRIVATE "./Dependencies/GL3W/include")
target_include_directories(application_debug PRIVATE "./Dependencies/GLM")
target_link_directories(application_debug PRIVATE "./Dependencies/GLFW")
target_link_libraries(application_debug PRIVATE "glfw3")



add_executable(application_release ${ALL_CPP_FILES})
set_target_properties(application_release PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../Binaries/Release")
target_compile_options(application_release PUBLIC ${ALL_FLAGS} ${RELEASE_FLAGS})

target_include_directories(application_release PRIVATE ".")
target_include_directories(application_release PRIVATE "./Containers")
target_include_directories(application_release PRIVATE "./EntityEngine")
target_include_directories(application_release PRIVATE "./Renderer")
target_include_directories(application_release PRIVATE "./Utilities")
target_include_directories(application_release PRIVATE "./Utilities/Math")

target_include_directories(application_release PRIVATE "./Dependencies/GLFW/include")
target_include_directories(application_release PRIVATE "./Dependencies/GL3W/include")
target_include_directories(application_release PRIVATE "./Dependencies/GLM")
target_link_directories(application_release PRIVATE "./Dependencies/GLFW")
target_link_libraries(application_release PRIVATE "glfw3")
