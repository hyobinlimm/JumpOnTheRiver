#pragma once
/// <summary>
/// 2022. 02. 16 SON
/// </summary>
#include <vector>
#include "Object.h"
#include "HBVector2.h"
#include "Define.h"

class DesireD2D;
class Player;

class Camera : public Object
{
public:
	Camera();
	~Camera();

private:
	
	// 캐릭터와 카메라의 거리의 차를 담는 변수 
	HBVector2<float> m_Offset;


public:
	// 그리기(draw) 함수
	virtual void Draw() override;

	// 엔진을 받는다.
	virtual void Draw(DesireD2D* engine2d) override;

	// Update 함수
	virtual void Update() override;

	// 플레이어의 포지션을 받는 업데이트
	void UpdateCoordinate(Player* player);

	D2D1::Matrix3x2F GetViewTM();

};

