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

// Ű �Է��� �޴´�.
void CInput::GetKeyInput()
{
	m_LeftRight = KEY_STATE::NONE;
	m_JumpDown = KEY_STATE::NONE;
	m_Hold = KEY_STATE::NONE;

	// �ɴ� Ű�� ������ ��
	/// Ű�� ������ ���� �� �������� �Է��� ���� ���� ���ƾ� �Ѵ�.
 	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
 	{
 		//m_keyDown = true;
 		//m_keyState = KEY_STATE::DOWN;
 	}

	// �ɴ� Ű�� ������ ��
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		m_JumpDown = KEY_STATE::DOWN;
	}

	// �������� �ȵǰ�
	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		m_JumpDown = KEY_STATE::JUMP;
		//SoundManager::GetInstance()->Play(1, "Player_Jump");
	}

	// �¿� �̵��� ���� ��Ÿ��
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		m_LeftRight = KEY_STATE::LEFT;
		//SoundManager::GetInstance()->Play(1, "Player_Walk");
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		m_LeftRight = KEY_STATE::RIGHT;
	}

	// Ȧ�� Ű
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
