#pragma once

class Matrix
{
public:
	Matrix();
	~Matrix();

public:
	FLOAT m_M11;
	FLOAT m_M12;		// �⺻�� 
	FLOAT m_M21;
	FLOAT m_M22;		// �⺻�� : ũ�� ����, ȸ��, ���� ���� ��ȯ�� ����
	FLOAT m_M31; 
	FLOAT m_M32;		// offset : ���� ��ȯ�� ���� �� �� ������ ��ȯ�� ����

	// �� ��° ���� ���� �׻� 0.0, 0.0, 1.0
	// Direct2D�� ����(����) ��ȯ�� �����ϹǷ� 
	// ��ȯ ����� ���� ��ȯ ��Ŀ��� �� ��° ���� �����ϰ� 3x2 ��ķ� ����
	// FLOAT m_M13, m_M23, m_M23;
	
	// ��� ���ϱ�
	Matrix operator+(const Matrix& matrix);

	// ��� ����
	Matrix operator-(const Matrix& matrix);

	// ��� ���ϱ�
	Matrix operator*(const Matrix& matrix);

	Matrix MakeTranslateMatrix(int daltaX, int daltaY);
	Matrix MakeRotateMatrix(float angle);
	Matrix MakeScaleMatrix(float size);
	Matrix MakeYaxisSymmetryMatrix();

	static Matrix Identity();
};
