#pragma once
#include "pch.h"

/// <summary>
/// 사각형 충돌 감지
/// </summary>

class BoxCollision
{
public:
	BoxCollision();
	~BoxCollision();

private:
	//위치 좌표 
	POINT m_Pos;

public:
	bool m_isCollided;
	int AxisAlinedBoundingBox(D2D1_RECT_F rect1, D2D1_RECT_F rect2);
	void Move(POINT pos);

};

