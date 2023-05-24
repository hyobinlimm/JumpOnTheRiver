#pragma once

class Matrix
{
public:
	Matrix();
	~Matrix();

public:
	FLOAT m_M11;
	FLOAT m_M12;		// 기본값 
	FLOAT m_M21;
	FLOAT m_M22;		// 기본값 : 크기 조정, 회전, 기울기 선형 변환를 정의
	FLOAT m_M31; 
	FLOAT m_M32;		// offset : 선형 변환이 수행 된 후 적용할 변환을 정의

	// 세 번째 열의 값은 항상 0.0, 0.0, 1.0
	// Direct2D는 아핀(선형) 변환만 지원하므로 
	// 변환 행렬은 이전 변환 행렬에서 세 번째 열을 생략하고 3x2 행렬로 정의
	// FLOAT m_M13, m_M23, m_M23;
	
	// 행렬 더하기
	Matrix operator+(const Matrix& matrix);

	// 행렬 빼기
	Matrix operator-(const Matrix& matrix);

	// 행렬 곱하기
	Matrix operator*(const Matrix& matrix);

	Matrix MakeTranslateMatrix(int daltaX, int daltaY);
	Matrix MakeRotateMatrix(float angle);
	Matrix MakeScaleMatrix(float size);
	Matrix MakeYaxisSymmetryMatrix();

	static Matrix Identity();
};
