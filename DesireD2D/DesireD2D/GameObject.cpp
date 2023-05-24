#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "Animator.h"
#include "Shape.h"
#include "ImageLoader.h"
#include "HBSprite.h"

GameObject::GameObject()
	: m_pTransform(new Transform()), // 모든 게임오브젝트는 생성과 동시에 트랜스폼을 가진다.
	m_IsCollided(false), m_CollisionBox()
{
}

GameObject::~GameObject()
{
	if (m_pTransform != nullptr)
	{
		delete m_pTransform;
	}
}

D2D1_RECT_F GameObject::GetWorldCollisionBox() const
{
	D2D1_POINT_2F _leftTop = D2D1::Point2F(m_CollisionBox.left, m_CollisionBox.top);
	D2D1_POINT_2F _rightBottom = D2D1::Point2F(m_CollisionBox.right, m_CollisionBox.bottom);

	D2D1::Matrix3x2F _world = m_pTransform->GetWorldTransformMatrix();
	D2D1_POINT_2F _worldLT = _leftTop * _world;
	D2D1_POINT_2F _worldRB = _rightBottom * _world;

	_leftTop.x = min(_worldLT.x, _worldRB.x);
	_leftTop.y = min(_worldLT.y, _worldRB.y);
	_rightBottom.x = max(_worldLT.x, _worldRB.x);
	_rightBottom.y = max(_worldLT.y, _worldRB.y);

	D2D1_RECT_F _worldCollisionBox = D2D1::RectF(_leftTop.x, _leftTop.y, _rightBottom.x, _rightBottom.y);

	return _worldCollisionBox;
}
