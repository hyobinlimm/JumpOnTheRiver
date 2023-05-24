#pragma once

#include <map>

struct SKeyState
{
	bool m_PressNow;
	bool m_IsJustUp;
	bool m_IsJustDown;
};


class SmartInput
{
public:
	void Initialize();

	void Update();

	void CheckKey(int virtualKey);


	bool m_VKSPACE_IsDown;	// ���� �����ӿ� �����ִ°�?
	bool m_VKSPACE_IsJustDOWN;	// �������� �ȴ����ִٰ� ���� ���ȴ°�?
	bool m_VKSPACE_IsJustUP;	// �������� �����ִٰ� ���� �������°�?

	std::map<int, SKeyState> m_KeyStates;


	bool IsKeyPress(int virtualKey);
	bool IsKeyJustUp(int virtualKey);
	bool IsKeyJustDown(int virtualKey);

};

