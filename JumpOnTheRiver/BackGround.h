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
	// �׸���(draw) �Լ�
	virtual void Draw() override;

	virtual void Draw(DesireD2D* engine2D) override; // ���߿� ��� Ŭ������ �ִ� �� �ϳ��� �����ϰ� �ؾ� ��. 

	// Update �Լ�
	virtual void Update() override;
};

