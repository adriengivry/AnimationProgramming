/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include <unordered_map>
#include <Windows.h>

namespace AnimationProgramming::Input
{
	class InputManager final
	{
	public:
		/**
		* Contructor of the InputManager
		*/
		InputManager() = default;

		/**
		* Update the input manager
		*/
		void Update();

		/**
		* Check if the given key is pressed
		* @param p_key
		*/
		bool IsKeyPressed(char p_key);

		/**
		* Check if the given key has been pressed during this frame
		* @param p_key
		*/
		bool IsKeyEventOccured(char p_key);

	private:
		std::unordered_map<char, bool> m_keyEvents;
		std::unordered_map<char, bool> m_keyStates;
	};
}

#endif // _INPUTMANAGER_H
