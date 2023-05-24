#pragma once
#include "pch.h"

/// <summary>
/// 그려질 모든 도형들의 클래스
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
	// 도형의 중점
	HBVector2<float> m_CenterPos;

public:
	float m_radius;
	float m_radiusX;
	float m_radiusY;
	
	D2D1_RECT_F m_collisionBox;

public:
	void SetCenterPos(HBVector2<float> val) { m_CenterPos = val; }
	
	// 도형의 크기를 넣는 함수 or 생성자에 넣어주자.  
	void CreateEllipse();
	D2D1_RECT_F CreateRectangle();

};

