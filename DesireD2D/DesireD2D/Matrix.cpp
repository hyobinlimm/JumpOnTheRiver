#include "pch.h"
#include "Matrix.h"
#include <math.h>

Matrix::Matrix()
	: m_M11(0), m_M12(0), m_M21(0), m_M22(0), m_M31(0), m_M32(0)
{
}

Matrix::~Matrix()
{
}

Matrix Matrix::operator+(const Matrix& matrix)
{
	Matrix tempMatrix;

	tempMatrix.m_M11 = tempMatrix.m_M11 + matrix.m_M11;
	tempMatrix.m_M12 = tempMatrix.m_M12 + matrix.m_M12;
	tempMatrix.m_M21 = tempMatrix.m_M21 + matrix.m_M21;
	tempMatrix.m_M22 = tempMatrix.m_M22 + matrix.m_M22;
	tempMatrix.m_M31 = tempMatrix.m_M31 + matrix.m_M31;
	tempMatrix.m_M32 = tempMatrix.m_M32 + matrix.m_M32;

	return tempMatrix;
}

Matrix Matrix::operator-(const Matrix& matrix)
{
	Matrix tempMatrix;

	tempMatrix.m_M11 = tempMatrix.m_M11 - matrix.m_M11;
	tempMatrix.m_M12 = tempMatrix.m_M12 - matrix.m_M12;
	tempMatrix.m_M21 = tempMatrix.m_M21 - matrix.m_M21;
	tempMatrix.m_M22 = tempMatrix.m_M22 - matrix.m_M22;
	tempMatrix.m_M31 = tempMatrix.m_M31 - matrix.m_M31;
	tempMatrix.m_M32 = tempMatrix.m_M32 - matrix.m_M32;

	return tempMatrix;
}

Matrix Matrix::operator*(const Matrix& matrix)
{
	Matrix tempMatrix; 

	tempMatrix.m_M11 = (this->m_M11 * matrix.m_M11) + (this->m_M12 * matrix.m_M21) + (0 * matrix.m_M31);
	tempMatrix.m_M12 = (this->m_M11 * matrix.m_M12) + (this->m_M12 * matrix.m_M22) + (0 * matrix.m_M32);
	tempMatrix.m_M21 = (this->m_M21 * matrix.m_M11) + (this->m_M22 * matrix.m_M21) + (0 * matrix.m_M31);
	tempMatrix.m_M22 = (this->m_M21 * matrix.m_M12) + (this->m_M22 * matrix.m_M22) + (0 * matrix.m_M32);
	tempMatrix.m_M31 = (this->m_M31 * matrix.m_M11) + (this->m_M32 * matrix.m_M21) + (1 * matrix.m_M31);
	tempMatrix.m_M32 = (this->m_M31 * matrix.m_M12) + (this->m_M32 * matrix.m_M22) + (1 * matrix.m_M32);

	return tempMatrix;
}

Matrix Matrix::MakeTranslateMatrix(int daltaX, int daltaY)
{
	Matrix tempMatrix;

	tempMatrix.m_M11 = 1; tempMatrix.m_M12 = 0;
	tempMatrix.m_M21 = 0; tempMatrix.m_M22 = 1;
	tempMatrix.m_M31 = (float)daltaX; tempMatrix.m_M32 = (float)daltaY;

	return tempMatrix;
}

Matrix Matrix::MakeRotateMatrix(float angle)
{
	Matrix tempMatrix;

	tempMatrix.m_M11 = (float)cos(angle); tempMatrix.m_M12 = -(float)sin(angle);
	tempMatrix.m_M21 = (float)sin(angle); tempMatrix.m_M22 = (float)cos(angle);

	return tempMatrix;
}

Matrix Matrix::MakeScaleMatrix(float size)
{
	Matrix tempMatrix;

	// 키울 사이즈 만큼을 행렬에 대입하자. 
	tempMatrix.m_M11 = size; tempMatrix.m_M12 = 0; 
	tempMatrix.m_M21 = 0; tempMatrix.m_M22 = size; 

	return tempMatrix;
}

Matrix Matrix::MakeYaxisSymmetryMatrix()
{
	Matrix tempMatrix;

	tempMatrix.m_M11 = -1; tempMatrix.m_M12 = 0;
	tempMatrix.m_M21 = 0; tempMatrix.m_M22 = 1;
	tempMatrix.m_M31 = 0; tempMatrix.m_M32 = 0;

	return tempMatrix;
}

Matrix Matrix::Identity()
{
	Matrix tempMatrix;

	tempMatrix.m_M11 = 1; tempMatrix.m_M12 = 0;
	tempMatrix.m_M21 = 0; tempMatrix.m_M22 = 1;
	tempMatrix.m_M31 = 0; tempMatrix.m_M32 = 0;

	return tempMatrix;
}

