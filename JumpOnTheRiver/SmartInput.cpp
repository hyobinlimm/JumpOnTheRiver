#include "SmartInput.h"
#include <windows.h>


void SmartInput::Initialize()
{
	m_KeyStates.insert({ VK_SPACE, SKeyState() });
	m_KeyStates.insert({ VK_LEFT, SKeyState() });
	m_KeyStates.insert({ VK_RIGHT, SKeyState() });
	m_KeyStates.insert({ VK_UP, SKeyState() });
	m_KeyStates.insert({ VK_DOWN, SKeyState() });
	m_KeyStates.insert({ VK_ESCAPE, SKeyState() });
	m_KeyStates.insert({ VK_F1, SKeyState() });
}

void SmartInput::Update()
{
	// 나의 키 셋의 상태를 모두 조사
	for (auto kvp : m_KeyStates)
	{
		CheckKey(kvp.first);
	}
}

void SmartInput::CheckKey(int virtualKey)
{
	// 지금 눌렸다면
	if (GetAsyncKeyState(virtualKey) & 0x8000)
	{
		// 이전까지 안눌려 있다가
		if (m_KeyStates[virtualKey].m_PressNow == false)
		{
			m_KeyStates[virtualKey].m_IsJustDown = true;
		}

		// 눌렸다
		m_KeyStates[virtualKey].m_PressNow = true;
	}
	// 지금 안눌린 상태라면
	else
	{
		// 이전까지 눌려져 있다가
		if (m_KeyStates[virtualKey].m_PressNow == true)
		{
			m_KeyStates[virtualKey].m_IsJustUp = true;
		}

		// 눌리지 않았다.
		m_KeyStates[virtualKey].m_PressNow = false;
	}
}

bool SmartInput::IsKeyPress(int virtualKey)
{
	return m_KeyStates[virtualKey].m_PressNow;
}

bool SmartInput::IsKeyJustUp(int virtualKey)
{
	return m_KeyStates[virtualKey].m_IsJustUp;
}

bool SmartInput::IsKeyJustDown(int virtualKey)
{
	return m_KeyStates[virtualKey].m_IsJustDown;
}
