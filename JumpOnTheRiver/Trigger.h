#pragma once

#include "Object.h"

/// <summary>
/// 2022. 02. 07  Son + c h o
/// ��ȣ�ۿ��� �ϰ� �׼��� �ִ� ��ü
/// </summary>
class Trigger : public Object
{
private:

public:
	Trigger(float x, float y);
	~Trigger();

private:
	// ������ ������ ��ǥ�� �־�� �Ѵ�.
	HBVector2<float> m_Pos;

};

