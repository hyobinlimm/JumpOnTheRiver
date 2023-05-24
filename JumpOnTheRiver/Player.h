#pragma once
/// <summary>
/// 2022. 02. 07 The SON
/// 
/// �÷��̾� Ŭ���� : �׸��� �� �ҳ�
/// �÷��̾�� ��Ʈ�� �� �� �ִ� ��ü
/// </summary>
#include "Object.h"
#include <map>

class DesireD2D;

class Player : public Object
{
public:
	Player(PLAYER_TYPE type, float GroundPosY);
	~Player();

	void SetPlayerType(PLAYER_TYPE val) { m_PlayerType = val; }
	void SetGravity(float val) { m_Gravity = val; }
	void SetJumpPower(float val) { m_JumpPower = val; }

	/// virtual override
public:
	// �׸���(draw) �Լ�
	virtual void Draw() override;
	virtual void Draw(DesireD2D* engine2D) override;

private:
	void Draw_DebugData(DesireD2D* engine2D);

public:
	// Update �Լ�
	virtual void Update() override;

public:
	void FSM(KEY_STATE leftRight, KEY_STATE jumpDown, KEY_STATE hold);
private:
	void FSM_LeftRight(KEY_STATE state);		// ĳ���� �¿� �̵��� ó���Ѵ�.
	void FSM_JumpDown(KEY_STATE state);			// ĳ������ ������ �ɱ⸦ ó���Ѵ�.

	void FSM_JumpDownMotion(KEY_STATE state);	// ĳ������ ������ �ɱ⸦ ó���Ѵ�.


	void MoveProcess_Ground();
	void MoveProcess_InAir();
	void SetGroundPos();			// ���� �ʱ� ��ġ�� ������ش�. (�ӽ�)

	/// non override
public:
	void Move_Left();
	void Move_Right();
	void Move_Up();
	void Move_Down();
	void Sit_Down();
	void Jump();
	void Push();

public:
	bool IsMovable();

	/// �÷��̾ �ʿ� �� �͵�
private:
	PLAYER_TYPE m_PlayerType;	// �ҳ��ΰ� �׸����ΰ�?

	// ���� üũ�� ������
	CHARACTER_STATE m_State;	// ĳ������ ��ǥ ����
	MOVE_STATE m_MoveState;		// �̵� ���� ����

	/// �浹���� ����
	// �ڽ� collision check  
	bool m_isBoxCollided;		// �ڽ��� �꿩�ִ�.
	bool m_isPushing;			// �÷��̾ �ڽ��� �̴����ΰ�?

	/// �̵� ����
	float m_HorizontalSpeed;	// �̵��ӵ� - ��/��
	float m_VerticalSpeed;
	//float m_GroundPosY;			// �ڽ��� ���� ��ġ (�ҳ�� �׸��ڰ� �ٸ���)

	// ���߿� ���� ��
	float m_VelocityY;			// �ӵ�
	float m_Gravity;			// �߷�
	float m_JumpPower;			// ���ӵ�

	// ���� �����
	bool isSoundPlay;
public:
	/// ��������Ʈ ����
	OBJECT_TYPE m_IdleSprite;
	OBJECT_TYPE m_IdleAirSprite;
	OBJECT_TYPE m_WalkSprite;
	OBJECT_TYPE m_DownSprite;
	OBJECT_TYPE m_HoldSprite;

private:
	void ApplySpriteBySide(KEY_STATE side);


};

