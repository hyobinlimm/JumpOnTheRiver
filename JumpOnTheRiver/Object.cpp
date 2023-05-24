#include "Object.h"
#include "DesireD2D.h"
#include "Transform.h"


int Object::m_CreateIndex = 0;


Object::Object()
	: m_pos({0, 0}), m_ID(OBJECT_TYPE::DEFAULT), m_pEngine2D(nullptr), m_bTriggerCheck(false)
	, m_CollidedPosY(0.0f), m_CurrentIndex(0)
{
	// static�� �̿��ؼ� �����ڷ������� ����ũ�� �ε����� �ο� �� �ش�.
	m_UniqueIndex = m_CreateIndex++;
}

// Object::Object(float x, float y)
// 	: m_pos({ x, y }), m_ID(OBJECT_TYPE::DEFAULT), m_pEngine2D(nullptr), m_bTriggerCheck(false)
// 	, m_CollidedPosY(0.0f)
// {
// 
// }
// 
// Object::Object(HBVector2<float> pos)
// 	: m_pos(pos), m_ID(OBJECT_TYPE::DEFAULT), m_pEngine2D(nullptr), m_bTriggerCheck(false)
// 	, m_CollidedPosY(0.0f)
// {
// 
// }


Object::~Object()
{

}

void Object::Draw()
{

}

void Object::Draw(DesireD2D* engine2D)
{
	// �׳� ������Ʈ�� ������ �׸� �� ��
	//engine2D->DrawSprite(this, (int)m_ID, 0);
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
	engine2D->DrawCollisionRect_Dev(this->m_pos.m_x, this->m_pos.m_y, (int)this->m_ID, 0);
}

void Object::Update()
{

}

void Object::SetObjectType(OBJECT_TYPE type)
{
	m_ID = type;
}

void Object::SetSide(OBJECT_SIDE horizontal, OBJECT_SIDE vertical)
{
	if (horizontal == OBJECT_SIDE::LEFT)
	{
		if (vertical == OBJECT_SIDE::UP)
		{
			GetTransform()->SetScale({ -1, 1 });
		}
		else if (vertical == OBJECT_SIDE::DOWN)
		{
			GetTransform()->SetScale({ -1, -1 });
		}
	}
	else if (horizontal == OBJECT_SIDE::RIGHT)
	{
		if (vertical == OBJECT_SIDE::UP)
		{
			GetTransform()->SetScale({ 1, 1 });
		}
		else if (vertical == OBJECT_SIDE::DOWN)
		{
			GetTransform()->SetScale({ 1, -1 });
		}
	}
}

void Object::SetPosition(HBVector2<float> val)
{
	m_pos = val;

	ApplyPosToTransform();
	//GetTransform()->SetPosition(val);
}

// ������Ʈ�ܿ��� ������ �ִ� ��ġ���� Ʈ������ ������Ʈ�� �����Ų��.
void Object::ApplyPosToTransform()
{
	GetTransform()->SetPosition(m_pos);
}

void Object::CreateCollisionFromSpriteInfo(DesireD2D* pEngine)
{
	SetCollisionBox(pEngine->GetSpriteRect((int)m_ID, 0));
}

