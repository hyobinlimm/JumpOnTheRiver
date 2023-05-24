#pragma once
/// <summary>
/// 2022. 02. 07 The SON
/// 
/// 플레이어 클래스 : 그림자 및 소년
/// 플레이어는 컨트롤 할 수 있는 객체
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
	// 그리기(draw) 함수
	virtual void Draw() override;
	virtual void Draw(DesireD2D* engine2D) override;

private:
	void Draw_DebugData(DesireD2D* engine2D);

public:
	// Update 함수
	virtual void Update() override;

public:
	void FSM(KEY_STATE leftRight, KEY_STATE jumpDown, KEY_STATE hold);
private:
	void FSM_LeftRight(KEY_STATE state);		// 캐릭터 좌우 이동을 처리한다.
	void FSM_JumpDown(KEY_STATE state);			// 캐릭터의 점프와 앉기를 처리한다.

	void FSM_JumpDownMotion(KEY_STATE state);	// 캐릭터의 점프와 앉기를 처리한다.


	void MoveProcess_Ground();
	void MoveProcess_InAir();
	void SetGroundPos();			// 지면 초기 위치로 만들어준다. (임시)

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

	/// 플레이어에 필요 한 것들
private:
	PLAYER_TYPE m_PlayerType;	// 소녀인가 그림자인가?

	// 상태 체크용 변수들
	CHARACTER_STATE m_State;	// 캐릭터의 대표 상태
	MOVE_STATE m_MoveState;		// 이동 관련 상태

	/// 충돌감지 관련
	// 박스 collision check  
	bool m_isBoxCollided;		// 박스에 닿여있다.
	bool m_isPushing;			// 플레이어가 박스를 미는중인가?

	/// 이동 관련
	float m_HorizontalSpeed;	// 이동속도 - 좌/우
	float m_VerticalSpeed;
	//float m_GroundPosY;			// 자신의 지면 위치 (소녀와 그림자가 다르다)

	// 공중에 있을 때
	float m_VelocityY;			// 속도
	float m_Gravity;			// 중력
	float m_JumpPower;			// 가속도

	// 사운드 울려서
	bool isSoundPlay;
public:
	/// 스프라이트 관련
	OBJECT_TYPE m_IdleSprite;
	OBJECT_TYPE m_IdleAirSprite;
	OBJECT_TYPE m_WalkSprite;
	OBJECT_TYPE m_DownSprite;
	OBJECT_TYPE m_HoldSprite;

private:
	void ApplySpriteBySide(KEY_STATE side);


};

