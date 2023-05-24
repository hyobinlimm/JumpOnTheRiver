#pragma once
#include "pch.h"

/// <summary>
/// ���� �̿��� �浹����  
/// </summary>

class CircleCollision
{
public:
	CircleCollision();
	~CircleCollision();

private:
	// ��ġ
	POINT m_Pos;
	POINT m_Radius;

public:
	// �浹�ߴ°�? 
	bool m_isCollided;
	
	int CheckCollision(D2D1_ELLIPSE ellipse1, D2D1_ELLIPSE ellipse2);
	void Move(POINT pos);
};

