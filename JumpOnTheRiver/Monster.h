#pragma once
/// 2022. 02. 07  Son + c h o
#include "Object.h"
#include "Position2D.h"

class Monster : public Object 
{
public:
	Monster();
	~Monster();

public:
	// �׸���(draw) �Լ�
	virtual void Draw() override;

	// Update �Լ�
	virtual void Update() override;

	/// ���Ϳ� �ʿ��� ��
private:

};

