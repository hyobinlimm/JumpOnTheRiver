#pragma once

#include "Define.h"
#include "ObjectManager.h"

/// <summary>
/// 게임의 키 입력을 받는다.
/// 물리적인 키 입력을 상태로 변환한다.
/// 
/// 2022.02.21 LeHideHome
/// </summary>
class CInput
{
public:
	CInput();
	~CInput();

	// 키 입력을 받는다.
	void GetKeyInput();

public:
	// 키의 상태. 한 개의 상태끼리는 동시입력이 불가함
	KEY_STATE m_LeftRight;		// 좌 또는 우	 (동시입력 불가)
	KEY_STATE m_JumpDown;		// 점프 또는 앉기 (동시입력 불가)
	KEY_STATE m_Hold;			// 상자를 밀 때 홀드 (상호작용 버튼(밀기))

	KEY_STATE m_DebugKeyState;

};

