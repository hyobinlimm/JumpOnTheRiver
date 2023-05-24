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
	// 그리기(draw) 함수
	virtual void Draw() override;

	// Update 함수
	virtual void Update() override;

	/// 몬스터에 필요한 것
private:

};

