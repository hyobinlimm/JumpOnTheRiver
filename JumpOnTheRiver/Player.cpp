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
	// �÷��̾� ������Ʈ�� �ִϸ��̼�
	engine2D->PlayAnimation(this, (int)m_ID, &m_CurrentIndex);

	// �浹���� ����
	if (m_IsCollided)
	{
		engine2D->DrawRectangleR(GetCollisionBox(), GetTransform()->GetWorldTransformMatrix());
	}
	else
	{
		engine2D->DrawRectangle(GetCollisionBox(), GetTransform()->GetWorldTransformMatrix());
	}

	// ��������Ʈ ����
	engine2D->DrawCollisionRect_Dev(m_pos.m_x, m_pos.m_y, (int)m_ID, 0);

	Draw_DebugData(engine2D);
}

// �� �ڽ��� ����� �����͸� ����Ѵ�.
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
	// ĳ������ �浹����

	// ĳ������ ���¿� ���� �̵� ó���� �� �ش�.
	if (m_MoveState == MOVE_STATE::AIR)
	{
		MoveProcess_InAir();
	}
	else
	{
		MoveProcess_Ground();
	}

	/// �ڽ��� �а� �;��
	//if (m_keyHoldRight)
	//{
	//	//posX += 4.0f;
	//	//m_pEngine2D->EllipseMove(m_pEngine2D->m_ellipse1, posX, posY);
	//	// m_pEngine2D->RectangleMove(m_pEngine2D->m_rectangle1, posX, posY);
	//	// �ڽ� ��������Ʈ�� ���� �������� �̵�
	//}

	//if (m_keyHoldLeft)
	//{
	//	//posX -= 4.0f;
	//	//m_pEngine2D->EllipseMove(m_pEngine2D->m_ellipse1, posX, posY);
	//	//m_pEngine2D->RectangleMove(m_pEngine2D->m_rectangle1, posX, posY);
	//	// �ڽ� ��������Ʈ�� ���� �������� �̵�
	//}
}

// keyinput �� ���� ĳ������ ������ ��������Ʈ ��ȯ
void Player::FSM(KEY_STATE leftRight, KEY_STATE jumpDown, KEY_STATE hold)
{
	/// ///////////////////////////////////////////////////////////////////////
	/// �Է� ���̾�

	/// �׾��ִٸ� �翬��.. ��� ���� �����̸� �ƹ��͵� ���� �ʴ´�.

	/// ���鿡 �پ��ֳ�/���� ���ΰ��� ����
	// �����̸� ������ ���� ����
	if (m_MoveState == MOVE_STATE::AIR)
	{
		// �¿� �Է� ó���� �޴´�.
		FSM_LeftRight(leftRight);
	}
	// ������ ���..
	else if (m_MoveState == MOVE_STATE::GROUND)
	{
		// �¿� �Է� ó���� �޴´�.
		FSM_LeftRight(leftRight);

		// ���� ������ �ɱⰡ �ִٸ�, ���������� ������
		FSM_JumpDown(jumpDown);

		/// Ȧ�带 �Ѵٸ�
	}


	/// ///////////////////////////////////////////////////////////////////////
	/// ��������Ʈ ���̾�

	// �¿� ����
	ApplySpriteBySide(leftRight);

	/// �⺻ ���� ó��

	/// �׾��ִٸ� �翬��.. ��� ���� �����̸� �ƹ��͵� ���� �ʴ´�.

	/// ���鿡 �پ��ֳ�/���� ���ΰ��� ����

	// �����̸� ������ ���� ���
	if (m_MoveState == MOVE_STATE::AIR)
	{
		SetObjectType(m_IdleAirSprite);
	}
	// ������ ���..
	else if (m_MoveState == MOVE_STATE::GROUND)
	{
		// �⺻�����δ� ��� ���
		SetObjectType(m_IdleSprite);

		// �̵��� �ִٸ� �ȱ� ���
		if (leftRight == KEY_STATE::LEFT || leftRight == KEY_STATE::RIGHT)
		{
			SetObjectType(m_WalkSprite);
		}

		// ���� ������ �ɱⰡ �ִٸ�, ���������� ������
		if (jumpDown == KEY_STATE::DOWN)
		{
			SetObjectType(m_DownSprite);
		}

		// Ȧ��(�б�)
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

		// �Է��� ���ų� �� �� �Է��� ��� �ƹ� ��ȭ�� ���� �ʴ´�.
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
			// �׸��ڴ� ������ ����.
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
	// ���󿡼��� ���ӵ� ���� �ִٸ� ���⼭ ó��
	if (m_IsCollided == false)
	{
		m_MoveState = MOVE_STATE::AIR;
	}
}

// ���� ���� (���߿� �ִ� ����)������ �̵� ó��
void Player::MoveProcess_InAir()
{
	/// �߷� ���ӵ���ŭ �Ʒ��� �����Ѵ�.
	// ������ ��� �ȴٸ� �ٲ�� ��
	// 0.017�� ���߿� GetDeltaTime���� �ٲ��� ��. 
	m_VelocityY += m_Gravity * (float)0.017;

	/// �÷����� �浹����

	// ���� üũ
	if (m_IsCollided == true)
	{
		m_MoveState = MOVE_STATE::GROUND;

		// ���� ���鿡 ��Ҵٸ�, �ӵ��� 0���� ������ְ�, ���� ���·� ������ش�.
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
			m_pos.m_x -= m_HorizontalSpeed;	// deltaX ��ŭ ���������� �̵����� �ش�.
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

// ������ �ٸ���. ������ ����~ �� ���ĺ��� ��� ������ �Ǿ�� �Ѵ�.
void Player::Jump()
{
	/// FSM(Finite State Machine)�⺻ - ���� üũ

	// �������� ���ϴ� ���¸�, ������ �ȵȴ�.
	if (IsMovable())
	{
		// ������ ������ ���߿� �ִ� ���·� ������ش�.
		m_MoveState = MOVE_STATE::AIR;

		// �ӵ��� ���� �о��ش�.
		m_VelocityY = -m_JumpPower;

		/// �� �� ��� �ؾ� �Ǵµ�..
		/// BTP�̽��� ���� ���ؼ� ��ġ ������ �Ѵ�.
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

// �ڽ��� �̴� �Լ��� ���� ����.
void Player::Push()
{
	// ���࿡ �ڽ��� �÷��̾ �꿴��.
	if (m_isBoxCollided == true)
	{
		// ���� �ڽ��� �а� �ִ� ���·� ������ش�.
		m_isPushing = true;

		// �ڽ��� ��ġ�� �̵������ش�!
		SoundManager::GetInstance()->Play(1, "Box_Push");
	}
}

bool Player::IsMovable()
{
	// FSM

	// ���� ���¶�� �� �����δ�.
	if (m_State == CHARACTER_STATE::DIE)
	{
		return false;
	}

	// ���� ���¶�� �� �����δ�.
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
