#include "pch.h"
#include "Transform.h"
#include "Matrix.h"
#include <cmath>

Transform::Transform()
	:m_Position(0,0), m_Rotation(1, 0), m_Scale(1, 1),
	m_WorldTranslateMatrix(Matrix::Identity()), 
	m_WorldScaleMatrix(Matrix::Identity()), 
	m_WorldRotateMatrix(Matrix::Identity()),
	m_WorldTransformMatrix(Matrix::Identity())
{
	Scale();
	Rotate();
	Translate();
}

Transform::~Transform()
{
	m_Scale = {NULL, NULL};
	m_Rotation = {NULL, NULL};
	m_Position = {NULL, NULL};
}

void Transform::Update()
{
	m_WorldTransformMatrix = m_WorldScaleMatrix * m_WorldRotateMatrix * m_WorldTranslateMatrix;
}

void Transform::SetScale(HBVector2<float> val)
{
	m_Scale = val;

	Scale();
}

void Transform::SetRotation(float val)
{
	float radian = (float)DEGTORAD(val); // ���� ���� ������ ȣ�������� �ٲ�. 
	
	float _x = (m_Rotation.m_x*cos(radian)) - (m_Rotation.m_y * sin(radian));
	float _y = (m_Rotation.m_x*sin(radian)) + (m_Rotation.m_y * cos(radian));

	m_Rotation.m_x = _x;
	m_Rotation.m_y = _y;
	
	m_Rotation.Normalize();

	Rotate();
}

void Transform::SetPosition(HBVector2<float> val)
{
	// ��������ڸ� ������� ������ �ٷ� ���� ����. 
	m_Position = val;

	// �׸��� �׸��� ��ķ� �׸���. 
	Translate();
}

void Transform::Scale()
{
	m_WorldScaleMatrix.m_M11 = m_Scale.m_x;
	m_WorldScaleMatrix.m_M22 = m_Scale.m_y;

	Update();
}

void Transform::Rotate()
{
	m_WorldRotateMatrix.m_M11 = m_Rotation.m_x;
	m_WorldRotateMatrix.m_M12 = -m_Rotation.m_y;
	m_WorldRotateMatrix.m_M21 = m_Rotation.m_y;
	m_WorldRotateMatrix.m_M22 = m_Rotation.m_x;

	Update();
}

void Transform::Translate()
{
	// �� matrix�� �ٲ��ش�. 
	m_WorldTranslateMatrix.m_M31 = this->GetPosition().m_x;
	m_WorldTranslateMatrix.m_M32 = this->GetPosition().m_y;
	
	// ��ġ�� �ݿ��� ��Ʈ������ �ֽ�ȭ ���ش�. 
	Update();
}

D2D1::Matrix3x2F Transform::GetWorldTransformMatrix()
{
	D2D1::Matrix3x2F _result;

	_result._11 = m_WorldTransformMatrix.m_M11;
	_result._12 = m_WorldTransformMatrix.m_M12;
	_result._21 = m_WorldTransformMatrix.m_M21;
	_result._22 = m_WorldTransformMatrix.m_M22;
	_result._31 = m_WorldTransformMatrix.m_M31;
	_result._32 = m_WorldTransformMatrix.m_M32;

	return _result;
}

