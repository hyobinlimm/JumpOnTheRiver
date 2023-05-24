#include "BackGround.h"
#include "Transform.h"
#include "DesireD2D.h"

BackGround::BackGround()
{
}

BackGround::BackGround(float x, float y)
{
}

BackGround::BackGround(Position2D pos)
{
}

BackGround::~BackGround()
{
}

void BackGround::Draw()
{
}

void BackGround::Draw(DesireD2D* engine2D)
{
	Transform* trans = GetTransform();
	HBVector2<float> JieunPos = trans->GetPosition();
	engine2D->DrawSprite((int)this->m_ID, 0, (int)JieunPos.m_x, (int)JieunPos.m_y);
}

void BackGround::Update()
{
	// 구름 배경의 위치를 옮겨주기. 
	Transform* trans = GetTransform(); 
	// 현재 포지션에서 x좌표로 -1만큼 이동한다는 뜻. 포지션이 다 벡터로 되어있어서 벡터 갖고 옴. 
	HBVector2<float> JieunPos = trans->GetPosition();
	JieunPos.m_x -= 0.5; // 벡터 뺄셈 여기서 기능함. 
	trans->SetPosition(JieunPos);
}
