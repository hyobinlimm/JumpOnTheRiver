#include "SoundManager.h"
#include "Player.h"

#include "Define.h"
#include "DesireD2D.h"
#include "Transform.h"
#include "Animator.h"
#include "Shape.h"
#include <string>


Player::Player(PLAYER_TYPE type, float GroundPosY)
	: m_PlayerType(type),
	m_State(), m_MoveState(),
	m_HorizontalSpeed(4.0f), m_VerticalSpeed(1.0f),
	m_VelocityY(0), m_Gravity(30.0f), m_JumpPower(50), m_isPushing(false), m_isBoxCollided(false),
	m_IdleSprite(OBJECT_TYPE::girl_idle), m_IdleAirSprite(OBJECT_TYPE::girl_jump),
	m_WalkSprite(OBJECT_TYPE::girl_walk), m_DownSprite(OBJECT_TYPE::girl_crouch),
	m_HoldSprite(OBJECT_TYPE::girl_push)
{

}

Player::~Player()
{

}

void Player::Draw()
{

}

void Player::Draw(DesireD2D* engine2D)
{
	// 플레이어 오브젝트는 애니메이션
	engine2D->PlayAnimation(this, (int)m_ID, &m_CurrentIndex);

	// 충돌감지 영역
	if (m_IsCollided)
	{
		engine2D->DrawRectangleR(GetCollisionBox(), GetTransform()->GetWorldTransformMatrix());
	}
	else
	{
		engine2D->DrawRectangle(GetCollisionBox(), GetTransform()->GetWorldTransformMatrix());
	}

	// 스프라이트 영역
	engine2D->DrawCollisionRect_Dev(m_pos.m_x, m_pos.m_y, (int)m_ID, 0);

	Draw_DebugData(engine2D);
}

// 나 자신의 디버그 데이터를 출력한다.
void Player::Draw_DebugData(DesireD2D* engine2D)
{
	float _XPos = 100.0f;
	if (m_PlayerType == PLAYER_TYPE::GIRL) _XPos = 100.0f;
	else if (m_PlayerType == PLAYER_TYPE::SHADOW) _XPos = 300.0f;

	float _YPos = 100.0f;
	std::string _PlayerType = ConvertState(m_PlayerType);
	std::string _PlayerState = ConvertState(m_State);
	std::string _PlayMoveState = ConvertState(m_MoveState);
	std::string _PlayPos = std::to_string(m_pos.m_x);
	_PlayPos.append(" / ");
	_PlayPos.append(std::to_string(m_pos.m_y));

	engine2D->SetTransformLocal();
	engine2D->DrawText(_XPos, _YPos, _PlayerType.c_str());
	engine2D->DrawText(_XPos, (_YPos += 20.0f), _PlayerState.c_str());
	engine2D->DrawText(_XPos, (_YPos += 20.0f), _PlayMoveState.c_str());
	engine2D->DrawText(_XPos, (_YPos += 20.0f), _PlayPos.c_str());
}

void Player::Update()
{
	// 캐릭터의 충돌감지

	// 캐릭터의 상태에 따라서 이동 처리를 해 준다.
	if (m_MoveState == MOVE_STATE::AIR)
	{
		MoveProcess_InAir();
	}
	else
	{
		MoveProcess_Ground();
	}

	/// 박스를 밀고 싶어요
	//if (m_keyHoldRight)
	//{
	//	//posX += 4.0f;
	//	//m_pEngine2D->EllipseMove(m_pEngine2D->m_ellipse1, posX, posY);
	//	// m_pEngine2D->RectangleMove(m_pEngine2D->m_rectangle1, posX, posY);
	//	// 박스 스프라이트도 같은 방향으로 이동
	//}

	//if (m_keyHoldLeft)
	//{
	//	//posX -= 4.0f;
	//	//m_pEngine2D->EllipseMove(m_pEngine2D->m_ellipse1, posX, posY);
	//	//m_pEngine2D->RectangleMove(m_pEngine2D->m_rectangle1, posX, posY);
	//	// 박스 스프라이트도 같은 방향으로 이동
	//}
}

// keyinput 에 따른 캐릭터의 상태의 스프라이트 전환
void Player::FSM(KEY_STATE leftRight, KEY_STATE jumpDown, KEY_STATE hold)
{
	/// ///////////////////////////////////////////////////////////////////////
	/// 입력 레이어

	/// 죽어있다면 당연히.. 계속 죽은 상태이며 아무것도 되지 않는다.

	/// 지면에 붙어있나/점프 중인가에 따라서
	// 공중이면 무조건 공중 상태
	if (m_MoveState == MOVE_STATE::AIR)
	{
		// 좌우 입력 처리를 받는다.
		FSM_LeftRight(leftRight);
	}
	// 지상인 경우..
	else if (m_MoveState == MOVE_STATE::GROUND)
	{
		// 좌우 입력 처리를 받는다.
		FSM_LeftRight(leftRight);

		// 만약 점프와 앉기가 있다면, 최종적으로 적용함
		FSM_JumpDown(jumpDown);

		/// 홀드를 한다면
	}


	/// ///////////////////////////////////////////////////////////////////////
	/// 스프라이트 레이어

	// 좌우 방향
	ApplySpriteBySide(leftRight);

	/// 기본 상태 처리

	/// 죽어있다면 당연히.. 계속 죽은 상태이며 아무것도 되지 않는다.

	/// 지면에 붙어있나/점프 중인가에 따라서

	// 공중이면 무조건 공중 모션
	if (m_MoveState == MOVE_STATE::AIR)
	{
		SetObjectType(m_IdleAirSprite);
	}
	// 지상인 경우..
	else if (m_MoveState == MOVE_STATE::GROUND)
	{
		// 기본적으로는 대기 모션
		SetObjectType(m_IdleSprite);

		// 이동이 있다면 걷기 모션
		if (leftRight == KEY_STATE::LEFT || leftRight == KEY_STATE::RIGHT)
		{
			SetObjectType(m_WalkSprite);
		}

		// 만약 점프와 앉기가 있다면, 최종적으로 적용함
		if (jumpDown == KEY_STATE::DOWN)
		{
			SetObjectType(m_DownSprite);
		}

		// 홀드(밀기)
		if (hold == KEY_STATE::HOLD)
		{
			SetObjectType(m_HoldSprite);
		}
	}
}

void Player::FSM_LeftRight(KEY_STATE state)
{
	switch (state)
	{
		case KEY_STATE::LEFT:
		{
			Move_Left();
		}
		break;

		case KEY_STATE::RIGHT:
		{
			Move_Right();
		}
		break;

		// 입력이 없거나 그 외 입력일 경우 아무 변화도 주지 않는다.
		default:
		{
		}
		break;
	}
}

void Player::FSM_JumpDown(KEY_STATE state)
{
	switch (state)
	{
		case KEY_STATE::JUMP:
		{
			Jump();
		}
		break;

		case KEY_STATE::DOWN:
		{
			// 그림자는 반응이 없다.
			if (m_PlayerType == PLAYER_TYPE::GIRL)
			{
				Sit_Down();
			}
		}
		break;

		case KEY_STATE::HOLD:
		{
			Push();
		}
		break;
	}
}

void Player::MoveProcess_Ground()
{
	// 지상에서의 가속도 등이 있다면 여기서 처리
	if (m_IsCollided == false)
	{
		m_MoveState = MOVE_STATE::AIR;
	}
}

// 점프 상태 (공중에 있는 상태)에서의 이동 처리
void Player::MoveProcess_InAir()
{
	/// 중력 가속도만큼 아래로 가속한다.
	// 프레임 제어가 된다면 바꿔야 함
	// 0.017은 나중에 GetDeltaTime으로 바뀌어야 됨. 
	m_VelocityY += m_Gravity * (float)0.017;

	/// 플랫폼과 충돌감지

	// 착지 체크
	if (m_IsCollided == true)
	{
		m_MoveState = MOVE_STATE::GROUND;

		// 만약 지면에 닿았다면, 속도를 0으로 만들어주고, 지면 상태로 만들어준다.
		if (m_PlayerType == PLAYER_TYPE::GIRL)
		{
			m_VelocityY = 0.f;
			m_MoveState = MOVE_STATE::GROUND;
			SetGroundPos();
		}
		else if (m_PlayerType == PLAYER_TYPE::SHADOW)
		{
			m_VelocityY = 0.f;
			m_MoveState = MOVE_STATE::GROUND;
			SetGroundPos();
		}
	}

	m_pos.m_y += m_VelocityY;
	ApplyPosToTransform();
}

void Player::SetGroundPos()
{
	//m_pos.m_y = (m_CollidedPosY - 57.5f);
	m_pos.m_y = m_CollidedPosY;

	ApplyPosToTransform();
}

void Player::Move_Left()
{
	if (IsMovable())
	{
		if (!(m_pos.m_x < 30))
		{
			m_pos.m_x -= m_HorizontalSpeed;	// deltaX 만큼 순간적으로 이동시켜 준다.
		}
		else
		{
			m_pos.m_x = MINOFFSET_X;
		}
		ApplyPosToTransform();
	}
}

void Player::Move_Right()
{
	if (IsMovable())
	{
		if (!(m_pos.m_x > 5700))
		{
			m_pos.m_x += m_HorizontalSpeed;
			if (isSoundPlay == false)
			{
				SoundManager::GetInstance()->Play(1, "Player_Walk");
				isSoundPlay = true;
			}
			else
			{
				//isSoundPlay = false;
			}
		}
		else
		{
			m_pos.m_x = MAXOFFSET_X;
		}
		ApplyPosToTransform();
	}
}

void Player::Move_Up()
{
	if (IsMovable())
	{
		m_pos.m_y -= m_VerticalSpeed;
		ApplyPosToTransform();
	}
}

void Player::Move_Down()
{
	if (IsMovable())
	{
		m_pos.m_y += m_VerticalSpeed;
		ApplyPosToTransform();
	}
}

void Player::Sit_Down()
{
	if (m_State == CHARACTER_STATE::SIT)
	{
		m_State = CHARACTER_STATE::NORMAL;
	}
	else if (m_State == CHARACTER_STATE::NORMAL)
	{
		m_State = CHARACTER_STATE::SIT;
	}
}

// 점프는 다르다. 점프를 시작~ 한 이후부터 계속 적용이 되어야 한다.
void Player::Jump()
{
	/// FSM(Finite State Machine)기본 - 조건 체크

	// 움직이지 못하는 상태면, 점프도 안된다.
	if (IsMovable())
	{
		// 점프를 했으니 공중에 있는 상태로 만들어준다.
		m_MoveState = MOVE_STATE::AIR;

		// 속도를 위로 밀어준다.
		m_VelocityY = -m_JumpPower;

		/// 얘 좀 어떻게 해야 되는데..
		/// BTP이슈를 막기 위해서 위치 보정을 한다.
		if (m_PlayerType == PLAYER_TYPE::GIRL)
		{
			m_pos.m_y -= 50.0f;
			ApplyPosToTransform();
		}
		else
		{
			m_pos.m_y += 50.0f;
			ApplyPosToTransform();
		}
	}
	SoundManager::GetInstance()->Play(1, "Player_Jump");
}

// 박스를 미는 함수를 만들 예정.
void Player::Push()
{
	// 만약에 박스에 플레이어가 닿였다.
	if (m_isBoxCollided == true)
	{
		// 현재 박스를 밀고 있는 상태로 만들어준다.
		m_isPushing = true;

		// 박스의 위치를 이동시켜준다!
		SoundManager::GetInstance()->Play(1, "Box_Push");
	}
}

bool Player::IsMovable()
{
	// FSM

	// 죽은 상태라면 못 움직인다.
	if (m_State == CHARACTER_STATE::DIE)
	{
		return false;
	}

	// 앉은 상태라면 못 움직인다.
	if (m_State == CHARACTER_STATE::SIT)
	{
		return false;
	}

	return true;
}

void Player::ApplySpriteBySide(KEY_STATE side)
{
	if (m_PlayerType == PLAYER_TYPE::GIRL)
	{
		if (side == KEY_STATE::LEFT)
		{
			SetSide(OBJECT_SIDE::LEFT, OBJECT_SIDE::UP);
		}
		else if (side == KEY_STATE::RIGHT)
		{
			SetSide(OBJECT_SIDE::RIGHT, OBJECT_SIDE::UP);
		}
	}
	else
	{
		if (side == KEY_STATE::LEFT)
		{
			SetSide(OBJECT_SIDE::LEFT, OBJECT_SIDE::DOWN);
		}
		else if (side == KEY_STATE::RIGHT)
		{
			SetSide(OBJECT_SIDE::RIGHT, OBJECT_SIDE::DOWN);
		}
	}
}
