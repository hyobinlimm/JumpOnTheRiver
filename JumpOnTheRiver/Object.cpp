#include "Object.h"
#include "DesireD2D.h"
#include "Transform.h"


int Object::m_CreateIndex = 0;


Object::Object()
	: m_pos({0, 0}), m_ID(OBJECT_TYPE::DEFAULT), m_pEngine2D(nullptr), m_bTriggerCheck(false)
	, m_CollidedPosY(0.0f), m_CurrentIndex(0)
{
	// static을 이용해서 생성자레벨에서 유니크한 인덱스를 부여 해 준다.
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
	// 그냥 오브젝트는 정적인 그림 한 장
	//engine2D->DrawSprite(this, (int)m_ID, 0);
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

// 오브젝트단에서 가지고 있는 위치값을 트랜프폼 컴포넌트로 적용시킨다.
void Object::ApplyPosToTransform()
{
	GetTransform()->SetPosition(m_pos);
}

void Object::CreateCollisionFromSpriteInfo(DesireD2D* pEngine)
{
	SetCollisionBox(pEngine->GetSpriteRect((int)m_ID, 0));
}

