#pragma once

#include "Define.h"
#include "ObjectManager.h"

/// <summary>
/// ������ Ű �Է��� �޴´�.
/// �������� Ű �Է��� ���·� ��ȯ�Ѵ�.
/// 
/// 2022.02.21 LeHideHome
/// </summary>
class CInput
{
public:
	CInput();
	~CInput();

	// Ű �Է��� �޴´�.
	void GetKeyInput();

public:
	// Ű�� ����. �� ���� ���³����� �����Է��� �Ұ���
	KEY_STATE m_LeftRight;		// �� �Ǵ� ��	 (�����Է� �Ұ�)
	KEY_STATE m_JumpDown;		// ���� �Ǵ� �ɱ� (�����Է� �Ұ�)
	KEY_STATE m_Hold;			// ���ڸ� �� �� Ȧ�� (��ȣ�ۿ� ��ư(�б�))

	KEY_STATE m_DebugKeyState;

};

