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
	// ���� Ű ���� ���¸� ��� ����
	for (auto kvp : m_KeyStates)
	{
		CheckKey(kvp.first);
	}
}

void SmartInput::CheckKey(int virtualKey)
{
	// ���� ���ȴٸ�
	if (GetAsyncKeyState(virtualKey) & 0x8000)
	{
		// �������� �ȴ��� �ִٰ�
		if (m_KeyStates[virtualKey].m_PressNow == false)
		{
			m_KeyStates[virtualKey].m_IsJustDown = true;
		}

		// ���ȴ�
		m_KeyStates[virtualKey].m_PressNow = true;
	}
	// ���� �ȴ��� ���¶��
	else
	{
		// �������� ������ �ִٰ�
		if (m_KeyStates[virtualKey].m_PressNow == true)
		{
			m_KeyStates[virtualKey].m_IsJustUp = true;
		}

		// ������ �ʾҴ�.
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
