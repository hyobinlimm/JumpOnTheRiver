#pragma once
#include "pch.h"

/// <summary>
/// �簢�� �浹 ����
/// </summary>

class BoxCollision
{
public:
	BoxCollision();
	~BoxCollision();

private:
	//��ġ ��ǥ 
	POINT m_Pos;

public:
	bool m_isCollided;
	int AxisAlinedBoundingBox(D2D1_RECT_F rect1, D2D1_RECT_F rect2);
	void Move(POINT pos);

};

