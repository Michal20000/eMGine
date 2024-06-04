#include "Window.hpp"

#include <gl3w.h>
#include <glfw3.h>

// Containers
// EntityEngine
// Renderer
// Utilities or Essentials
// Directory for Fragments and
// Systems...

// TODO: cmake --build in ./Builds
// TODO: target_include_directories(...);
// TODO: target_link_libraries(...);
// TODO: ./Build.bat
// TODO: ./Build.bat --profile
// TODO: ./Build.bat --debug
// TODO: ./Build.bat --release
// TODO: ./Build.bat --cbench

// TODO: ./Run.bat --profile
// TODO: ./Run.bat --cbench --debug



int32_t main()
{
	// enum class KeyState
	// {
	// 	BEING_RELEASED = 0,
	// 	PRESSED = 1,
	// 	BEING_PRESSED = 2,
	// 	RELEASED = 3

	// };
	// enum class KeyCode
	// {
	// 	A, B, C, D, E, F, G ...

	// };

	// Keyboard.hpp
	// There are 4 states { UP; DOWN; UP_TO_DOWN; DOWN_TO_UP; };
	// Button(KeyCode::LEFT_CONTROL, KeyState::PRESSED, 0.0F);
	// TODO: { char State; float Duration; }

	// Mouse.hpp
	// There are 4 states { UP; DOWN; UP_TO_DOWN; DOWN_TO_UP; };
	// TODO: { LMB; MMB; RMB; }
	// TODO: { char State; float Duration; }
	// TODO: what if you want to rotate camera?
	// TODO: or check if UI element is clicked or things like that...

	// IO.hpp
	// Function ideas:
	// press_time
	// release_time
	
	// class ButtonData;
	// ButtonData info = Button(KeyCode::LEFT_CONTROL);
	// ButtonData info = Button("f", "pressed", 3.0F);
	// LOG(info.Duration());
	// LOG(info.State());
	// KEY_A; KEY_B;

	// IDEA: BEING_PRESSED;
	// IDEA: PRESSED;
	// IDEA: UP;
	// IDEA: BEING_RELEASED;
	// IDEA: RELEASED;
	// IDEA: DOWN;

	// CharacterDown
	// key_info.IsDown() & key_info.WasDown()
	// IDEA: was_down
	// IDEA: is_down
	// { 0, 0 } -> BEING_RELEASED; DOWN;
	// { 0, 1 } -> PRESSED; UP;
	// { 1, 1 } -> BEING_PRESSED; UP;
	// { 1, 0 } -> RELEASED; DOWN:

	Window window = Window("eMGine", 1280, 720);
	window.Main();

}