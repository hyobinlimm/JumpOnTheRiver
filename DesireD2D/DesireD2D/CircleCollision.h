#pragma once
#include "pch.h"

/// <summary>
/// 원을 이용한 충돌감지  
/// </summary>

class CircleCollision
{
public:
	CircleCollision();
	~CircleCollision();

private:
	// 위치
	POINT m_Pos;
	POINT m_Radius;

public:
	// 충돌했는가? 
	bool m_isCollided;
	
	int CheckCollision(D2D1_ELLIPSE ellipse1, D2D1_ELLIPSE ellipse2);
	void Move(POINT pos);
};

