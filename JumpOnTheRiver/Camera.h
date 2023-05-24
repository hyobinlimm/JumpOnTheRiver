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
	
	// ĳ���Ϳ� ī�޶��� �Ÿ��� ���� ��� ���� 
	HBVector2<float> m_Offset;


public:
	// �׸���(draw) �Լ�
	virtual void Draw() override;

	// ������ �޴´�.
	virtual void Draw(DesireD2D* engine2d) override;

	// Update �Լ�
	virtual void Update() override;

	// �÷��̾��� �������� �޴� ������Ʈ
	void UpdateCoordinate(Player* player);

	D2D1::Matrix3x2F GetViewTM();

};

