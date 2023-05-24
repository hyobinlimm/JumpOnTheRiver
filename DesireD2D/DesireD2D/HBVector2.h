#pragma once
#include "Matrix.h"

/// <summary>
/// 2차원 벡터를 정의
/// 
/// float, int 모두 가능해야함. 
/// </summary>

template<typename T>
class HBVector2
{
public:
	HBVector2();
	HBVector2(T _x, T _y);
	// 복사생성자
	HBVector2(const HBVector2<T>& vector2);


	~HBVector2();

	// 2차원 벡터의 성분
	T m_x;
	T m_y;

	// 벡터와 벡터의 연산자들 (결과는 벡터)
	HBVector2<T> operator+(const HBVector2<T> vector2);
	HBVector2<T> operator-(const HBVector2<T> vector2);
	
	friend HBVector2<T> operator*(const float num, HBVector2<T> vector2);
	
	// 벡터와 행렬의 곱 (결과는 벡터)
	HBVector2<T> operator*(const Matrix matrix);

	// 벡터의 내적
	float DotProduct(HBVector2<T> vector2);

	HBVector2<T>& Normalize();

	float GetMagnitude(); // 벡터의 크기를 구하는 함수
};

template<typename T>
float HBVector2<T>::GetMagnitude()
{
	// 백터의 크기를 구하자. 
	return sqrtf(powf(m_x, 2) + powf(m_y, 2));
}

template<typename T>
HBVector2<T>& HBVector2<T>::Normalize()
{
	float lengthVector = GetMagnitude();

	this->m_x = this->m_x / lengthVector;
	this->m_y = this->m_y / lengthVector;

	return *this; // 나의 레퍼런스를 반환.
}

template<typename T>
HBVector2<T>::HBVector2()
	: m_x(0), m_y(0)
{

}

template<typename T>
HBVector2<T>::HBVector2(T _x, T _y)
	: m_x(_x), m_y(_y)
{

}

// 복사생성자
template<typename T>
HBVector2<T>::HBVector2(const HBVector2<T>& vector2)
{
	this->m_x = vector2.m_x;
	this->m_y = vector2.m_y;
}


template<typename T>
HBVector2<T>::~HBVector2()
{

}

template<typename T>
HBVector2<T> HBVector2<T>::operator+(const HBVector2<T> vector2)
{
	HBVector2<T> _tempD2;
	_tempD2.m_x = this->m_x + vector2.m_x;
	_tempD2.m_y = this->m_y + vector2.m_y;

	return _tempD2;
}

template<typename T>
HBVector2<T> HBVector2<T>::operator-(const HBVector2<T> vector2)
{
	HBVector2<T> _tempD2;
	_tempD2.m_x = this->m_x - vector2.m_x;
	_tempD2.m_y = this->m_y - vector2.m_y;

	return _tempD2;
}

template<typename T>
HBVector2<T> HBVector2<T>::operator*(const Matrix matrix)
{
	HBVector2<T> _result;

	_result.m_x = m_x * matrix.m_M11 + m_y * matrix.m_M21;
	_result.m_y = m_x * matrix.m_M12 + m_y * matrix.m_M22;

	return _result;
}

template<typename T>
HBVector2<T> operator*(const float num, HBVector2<T> vector2)
{
	HBVector2<T> _result;

	_result.m_x = num * vector2.m_x ;
	_result.m_y = num * vector2.m_y;

	return _result;
}

template<typename T>
float HBVector2<T>::DotProduct(HBVector2<T> vector2)
{
	return (this->m_x * vector2.m_x) + (this->m_y * vector2.m_y);
}

