#include "Camera.h"
#include "Transform.h"
#include "Player.h"
#include "DesireD2D.h"
#include "HBVector2.h"
#include "Define.h"

Camera::Camera()
{
	// ī�޶��� ��ġ�� �����. 
	m_pos = { 0 , 0 };
	ApplyPosToTransform();
}

Camera::~Camera()
{

}

void Camera::Draw()
{

}

void Camera::Draw(DesireD2D* engine2d)
{

}

void Camera::UpdateCoordinate(Player* player)
{
	// ���� �� ���̿��� ī�޶� �̵��� �� ���� �� ����
	const int _distanceMim = 960;
	const int _distanceMax = 4800;
	
	static float _prePosX = player->m_pos.m_x;
	float _curPosX = player->m_pos.m_x;
	
	// ������ ĳ���� ��ǥ�� ���� ĳ���� ��ǥ�� �� ��ŭ �����δ�. 
	m_Offset.m_x = _curPosX - _prePosX;

	if (!(_curPosX < _distanceMim || _distanceMax < _curPosX ))
	{
		this->m_pos.m_x += m_Offset.m_x;
	}
	
	ApplyPosToTransform();
	_prePosX = _curPosX;
}

D2D1::Matrix3x2F Camera::GetViewTM()
{
	// �ڽ��� Transform�� 
	D2D1::Matrix3x2F _myTransform = GetTransform()->GetWorldTransformMatrix();
	
	// ����ȯ(�����)
	D2D1InvertMatrix(&_myTransform);

	return _myTransform;
}

void Camera::Update()
{
	// �ƹ� �ϵ� ���� �ʴ´�.

	if (GetAsyncKeyState(VK__A) & 0x8001)
	{
		m_pos.m_x -= 10.0f;
		ApplyPosToTransform();
	}
	
	if (GetAsyncKeyState(VK__D) & 0x8001)
	{
		m_pos.m_x += 10.0f;
		ApplyPosToTransform();
	}
	
	if (GetAsyncKeyState(VK__W) & 0x8001)
	{
		m_pos.m_y -= 10.0f;
		ApplyPosToTransform();
	}
	
	if (GetAsyncKeyState(VK__S) & 0x8001)
	{
		m_pos.m_y += 10.0f;
		ApplyPosToTransform();
	}
}
