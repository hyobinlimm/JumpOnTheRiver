#pragma once
#include "HBVector2.h"

#define PI 3.141592
#define DEGTORAD(degree) (degree / 180) * PI

class Matrix;

/// <summary>
///  이동, 회전, 스케일을 조정하는 클래스
///  SRT순 으로 되어야 한다.  
/// </summary>

class Transform 
{
public:
	Transform();
	~Transform();
	
private:
	/// 스케일, 회전, 이동 시키는 함수
	// 모든 객체가 가지고 있는 트렌스폼.
	HBVector2<float> m_Scale;
	HBVector2<float> m_Rotation;
	HBVector2<float> m_Position;

	Matrix m_WorldTransformMatrix; // = s * r * t;

	Matrix m_WorldScaleMatrix;
	Matrix m_WorldRotateMatrix;
	Matrix m_WorldTranslateMatrix;


private:
	// m_WorldTransformMatrix를 바꿔준다. 
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
	
	// D2d행렬로 바꾸는 함수 
	D2D1::Matrix3x2F GetWorldTransformMatrix();

};

