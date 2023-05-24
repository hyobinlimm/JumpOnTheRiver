#include "Camera.h"
#include "Transform.h"
#include "Player.h"
#include "DesireD2D.h"
#include "HBVector2.h"
#include "Define.h"

Camera::Camera()
{
	// 카메라의 위치를 잡아줌. 
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
	// 맵의 총 길이에서 카메라가 이동할 수 없는 곳 설정
	const int _distanceMim = 960;
	const int _distanceMax = 4800;
	
	static float _prePosX = player->m_pos.m_x;
	float _curPosX = player->m_pos.m_x;
	
	// 과거의 캐릭터 좌표와 현재 캐릭터 좌표의 차 만큼 움직인다. 
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
	// 자신의 Transform의 
	D2D1::Matrix3x2F _myTransform = GetTransform()->GetWorldTransformMatrix();
	
	// 역변환(역행렬)
	D2D1InvertMatrix(&_myTransform);

	return _myTransform;
}

void Camera::Update()
{
	// 아무 일도 하지 않는다.

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
