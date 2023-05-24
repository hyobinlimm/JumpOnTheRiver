
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

	// 산술 오버플로가 발생할지도 모른다는 warring이 떠서 double 캐스트하여 연산. 
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
