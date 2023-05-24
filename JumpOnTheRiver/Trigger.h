#pragma once

#include "Object.h"

/// <summary>
/// 2022. 02. 07  Son + c h o
/// 상호작용을 하고 액션이 있는 객체
/// </summary>
class Trigger : public Object
{
private:

public:
	Trigger(float x, float y);
	~Trigger();

private:
	// 보이지 않지만 좌표는 있어야 한다.
	HBVector2<float> m_Pos;

};

