#pragma once
#include "HBVector2.h"

#define PI 3.141592
#define DEGTORAD(degree) (degree / 180) * PI

class Matrix;

/// <summary>
///  �̵�, ȸ��, �������� �����ϴ� Ŭ����
///  SRT�� ���� �Ǿ�� �Ѵ�.  
/// </summary>

class Transform 
{
public:
	Transform();
	~Transform();
	
private:
	/// ������, ȸ��, �̵� ��Ű�� �Լ�
	// ��� ��ü�� ������ �ִ� Ʈ������.
	HBVector2<float> m_Scale;
	HBVector2<float> m_Rotation;
	HBVector2<float> m_Position;

	Matrix m_WorldTransformMatrix; // = s * r * t;

	Matrix m_WorldScaleMatrix;
	Matrix m_WorldRotateMatrix;
	Matrix m_WorldTranslateMatrix;


private:
	// m_WorldTransformMatrix�� �ٲ��ش�. 
	void Update();

public:
	HBVector2<float> GetScale() const { return m_Scale; }
	void SetScale(HBVector2<float> val);
	
	HBVector2<float> GetRotation() const { return m_Rotation; }
	void SetRotation(float val);
	
	HBVector2<float> GetPosition() const { return m_Position; }
	void SetPosition(HBVector2<float> val);

	void Scale();

	void Rotate();
	
	void Translate();
	
	// D2d��ķ� �ٲٴ� �Լ� 
	D2D1::Matrix3x2F GetWorldTransformMatrix();

};

