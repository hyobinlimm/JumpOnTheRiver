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


	bool m_VKSPACE_IsDown;	// 현재 프레임에 눌려있는가?
	bool m_VKSPACE_IsJustDOWN;	// 이전까지 안눌려있다가 지금 눌렸는가?
	bool m_VKSPACE_IsJustUP;	// 이전까지 눌려있다가 지금 떨어졌는가?

	std::map<int, SKeyState> m_KeyStates;


	bool IsKeyPress(int virtualKey);
	bool IsKeyJustUp(int virtualKey);
	bool IsKeyJustDown(int virtualKey);

};

