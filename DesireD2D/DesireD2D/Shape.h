#pragma once
#include "pch.h"

/// <summary>
/// �׷��� ��� �������� Ŭ����
/// </summary>

class Shape
{
public:
	Shape();
	Shape(HBVector2<float> pos);
	Shape(HBVector2<float> pos, float radius);
	Shape(HBVector2<float> pos, float radiusX, float radiusY);
	Shape(float posX, float posY, float radius);
	Shape(float posX, float posY, float radiusX, float radiusY);
	~Shape();

private:
	// ������ ����
	HBVector2<float> m_CenterPos;

public:
	float m_radius;
	float m_radiusX;
	float m_radiusY;
	
	D2D1_RECT_F m_collisionBox;

public:
	void SetCenterPos(HBVector2<float> val) { m_CenterPos = val; }
	
	// ������ ũ�⸦ �ִ� �Լ� or �����ڿ� �־�����.  
	void CreateEllipse();
	D2D1_RECT_F CreateRectangle();

};

