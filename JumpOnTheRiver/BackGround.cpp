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
	// ���� ����� ��ġ�� �Ű��ֱ�. 
	Transform* trans = GetTransform(); 
	// ���� �����ǿ��� x��ǥ�� -1��ŭ �̵��Ѵٴ� ��. �������� �� ���ͷ� �Ǿ��־ ���� ���� ��. 
	HBVector2<float> JieunPos = trans->GetPosition();
	JieunPos.m_x -= 0.5; // ���� ���� ���⼭ �����. 
	trans->SetPosition(JieunPos);
}
