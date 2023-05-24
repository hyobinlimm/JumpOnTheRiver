#pragma once
#include "Position2D.h"
#include "Object.h"

class DesireD2D;

class BackGround : public Object
{
public:
	BackGround();
	BackGround(float x, float y);
	BackGround(Position2D pos);
	virtual ~BackGround();

public:
	// 그리기(draw) 함수
	virtual void Draw() override;

	virtual void Draw(DesireD2D* engine2D) override; // 나중엔 모든 클래스에 있는 걸 하나로 관리하게 해야 됨. 

	// Update 함수
	virtual void Update() override;
};

