#include "SoundManager.h"
#include "CInput.h"
#include "windows.h"

CInput::CInput()
	: m_JumpDown(KEY_STATE::NONE)
{

}

CInput::~CInput()
{

}

// 키 입력을 받는다.
void CInput::GetKeyInput()
{
	m_LeftRight = KEY_STATE::NONE;
	m_JumpDown = KEY_STATE::NONE;
	m_Hold = KEY_STATE::NONE;

	// 앉는 키를 눌렀을 때
	/// 키를 누르고 있을 때 연속적인 입력이 들어가는 것을 막아야 한다.
 	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
 	{
 		//m_keyDown = true;
 		//m_keyState = KEY_STATE::DOWN;
 	}

	// 앉는 키를 떼었을 때
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		m_JumpDown = KEY_STATE::DOWN;
	}

	// 이중점프 안되게
	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		m_JumpDown = KEY_STATE::JUMP;
		//SoundManager::GetInstance()->Play(1, "Player_Jump");
	}

	// 좌우 이동은 서로 배타적
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		m_LeftRight = KEY_STATE::LEFT;
		//SoundManager::GetInstance()->Play(1, "Player_Walk");
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		m_LeftRight = KEY_STATE::RIGHT;
	}

	// 홀드 키
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
	{
		m_Hold = KEY_STATE::HOLD;
	}

	if (GetAsyncKeyState(VK_F1) & 0x8001)
	{
		m_DebugKeyState = KEY_STATE::DEBUG_ALL;
	}

	if (GetAsyncKeyState(VK_F2) & 0x8001)
	{
		m_DebugKeyState = KEY_STATE::DEBUG_OBJECT;

	}

	if (GetAsyncKeyState(VK_F3) & 0x8001)
	{
		m_DebugKeyState = KEY_STATE::DEBUG_COLLISION;
	}

	//m_keyDownLastFrame = m_keyDown;
}
