#include "AnimationProgramming/Input/InputManager.h"

void AnimationProgramming::Input::InputManager::Update()
{
	m_keyEvents.clear();

	for (uint8_t i = 0; i < 255; ++i)
	{
		bool keyState = GetKeyState(static_cast<int>(i)) & 0x8000;
		m_keyEvents[i] = keyState && !m_keyStates[i]; /* Boolean = the key wasn't pressed and is now pressed */
		m_keyStates[i] = keyState;
	}
}

bool AnimationProgramming::Input::InputManager::IsKeyPressed(char p_key)
{
	return m_keyStates[p_key];
}

bool AnimationProgramming::Input::InputManager::IsKeyEventOccured(char p_key)
{
	return m_keyEvents[p_key];
}
