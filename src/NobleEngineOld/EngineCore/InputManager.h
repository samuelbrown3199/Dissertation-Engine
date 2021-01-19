#pragma once
#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <SDL.h>

namespace NobleEngine
{
	/**
	*Handles input for the engine.
	*/
	class InputManager
	{
	public:
		/**
		*Stores the mouse x and y positions.
		*/
		static int mouseX, mouseY;

		InputManager();
		~InputManager();
		/**
		*Checks if a key is down. Uses SDL keycodes which can be found here: https://wiki.libsdl.org/SDL_Scancode
		*/
		static bool IfKeyDown(SDL_Keycode key);
		/**
		*Checks if a mouse button is down. Button 0 is left, 1 is right, 2 is middle.
		*/
		static bool IfMouseButtonDown(int button);
		/**
		*Gets the mouse position and stores it in the mouse position variables.
		*/
		static void GetMousePosition();
	};
}
#endif

