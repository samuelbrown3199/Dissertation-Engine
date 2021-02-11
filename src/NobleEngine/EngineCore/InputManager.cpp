#include "InputManager.h"

#include <algorithm>

namespace NobleEngine
{
	int InputManager::mouseX = 0;
	int InputManager::mouseY = 0;

	std::vector<SDL_Scancode> InputManager::downKeys, InputManager::oldDownKeys;
	std::vector<SDL_Scancode> InputManager::upKeys;

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	bool InputManager::GetKey(SDL_Keycode key)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_GetScancodeFromKey(key)])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputManager::GetKeyDown(SDL_Keycode key)
	{
		for (int i = 0; i < downKeys.size(); i++)
		{
			if (downKeys.at(i) == SDL_GetScancodeFromKey(key))
			{
				if (std::find(oldDownKeys.begin(), oldDownKeys.end(), SDL_GetScancodeFromKey(key)) == oldDownKeys.end())
				{
					return true;
				}
			}
		}

		return false;
	}

	bool InputManager::GetKeyUp(SDL_Keycode key)
	{
		for (int i = 0; i < upKeys.size(); i++)
		{
			if (upKeys.at(i) == SDL_GetScancodeFromKey(key))
			{
				return true;
			}
		}

		return false;
	}

	bool InputManager::IfMouseButtonDown(int button)
	{
		if (button == 0)
		{
			if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				return true;
			}
		}
		else if (button == 1)
		{
			if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_RIGHT))
			{
				return true;
			}
		}
		else if (button == 2)
		{
			if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
			{
				return true;
			}
		}

		return false;
	}

	void InputManager::GetMousePosition()
	{
		SDL_GetMouseState(&mouseX, &mouseY);
	}

	void InputManager::ClearFrameKeys()
	{
		if (downKeys.size() != 0 || upKeys.size() != 0)
		{
			oldDownKeys = downKeys;

			std::cout << "Down keys this frame " << downKeys.size() << std::endl;
			std::cout << "Up keys this frame " << upKeys.size() << std::endl;

			downKeys.clear();
			upKeys.clear();
		}
	}
}