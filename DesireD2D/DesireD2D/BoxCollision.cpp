#include "pch.h"
#include "BoxCollision.h"

BoxCollision::BoxCollision()
	: m_Pos({0, }), m_isCollided(false)
{

}

BoxCollision::~BoxCollision()
{

}

int BoxCollision::AxisAlinedBoundingBox(D2D1_RECT_F rect1, D2D1_RECT_F rect2)
{
	if ((rect1.right > rect2.left && rect1.left < rect2.right) &&
		(rect1.bottom > rect2.top && rect1.top < rect2.bottom))
	{
		m_isCollided = true;
	}
	else
	{
		m_isCollided = false;
	}

	return m_isCollided;
}

void BoxCollision::Move(POINT pos)
{

}
