#include "pch.h"
#include "Shape.h"

Shape::Shape()
	: m_CenterPos({ 0, 0 }), m_radius(0), m_radiusX(0), m_radiusY(0), m_collisionBox({0,0,0,0})
{

}

Shape::Shape(HBVector2<float> pos)
	: m_CenterPos({ pos.m_x, pos.m_y }), m_radius(0), m_radiusX(0), m_radiusY(0), m_collisionBox({ 0,0,0,0 })
{

}



Shape::Shape(HBVector2<float> pos, float radius)
	: m_CenterPos(pos), m_radius(radius), m_radiusX(0), m_radiusY(0), m_collisionBox({ 0,0,0,0 })
{

}

Shape::Shape(float posX, float posY, float radius)
	: m_CenterPos({ posX, posY }), m_radius(radius), m_radiusX(0), m_radiusY(0), m_collisionBox({0,0,0,0})
{

}

Shape::Shape(float posX, float posY, float radiusX, float radiusY)
	: m_CenterPos({ posX, posY }), m_radius(0), m_radiusX(radiusX), m_radiusY(radiusY), m_collisionBox({0,0,0,0})
{

}

Shape::Shape(HBVector2<float> pos, float radiusX, float radiusY)
	: m_CenterPos(pos), m_radius(0), m_radiusX(radiusX), m_radiusY(radiusY), m_collisionBox({0,0,0,0})
{

}

Shape::~Shape()
{
	m_CenterPos = {NULL, NULL};
	m_radius = NULL;
	m_radiusX = NULL;
	m_radiusY = NULL;

	m_collisionBox = { NULL, NULL, NULL, NULL };
}

void Shape::CreateEllipse()
{
	D2D1::Ellipse(D2D1::Point2F(m_CenterPos.m_x, m_CenterPos.m_y), m_radius, m_radius);
}

D2D1_RECT_F Shape::CreateRectangle()
{
	if (m_radius != 0)
	{
		m_collisionBox = D2D1::RectF(m_CenterPos.m_x - m_radius, m_CenterPos.m_y - m_radius, m_CenterPos.m_x + m_radius, m_CenterPos.m_y + m_radius);

		return m_collisionBox;
	}
	else
	{
		m_collisionBox = D2D1::RectF(m_CenterPos.m_x - m_radiusX, m_CenterPos.m_y - m_radiusY, m_CenterPos.m_x + m_radiusX, m_CenterPos.m_y + m_radiusY);
		return m_collisionBox;
	}
}
