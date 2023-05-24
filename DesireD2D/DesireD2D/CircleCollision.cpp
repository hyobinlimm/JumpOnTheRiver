
#include "pch.h"
#include <math.h>
#include "CircleCollision.h"

CircleCollision::CircleCollision()
	:m_Pos({ 0, }), m_Radius({ 0, }), m_isCollided(false)
{

}

CircleCollision::~CircleCollision()
{

}

int CircleCollision::CheckCollision(D2D1_ELLIPSE ellipse1, D2D1_ELLIPSE ellipse2)
{
	float _radius = ellipse1.radiusX + ellipse2.radiusX;

	float _Direct;

	// ��� �����÷ΰ� �߻������� �𸥴ٴ� warring�� ���� double ĳ��Ʈ�Ͽ� ����. 
	_Direct = sqrtf(powf(ellipse2.point.x - ellipse1.point.x, 2) + powf(ellipse2.point.y - ellipse1.point.y, 2));

	if (_radius > _Direct)
	{
		 m_isCollided = true;
	}
	else
	{
		 m_isCollided = false;
	}

	return m_isCollided;
}

void CircleCollision::Move(POINT pos)
{

}
