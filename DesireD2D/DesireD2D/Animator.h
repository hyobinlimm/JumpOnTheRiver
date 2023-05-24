#pragma once

//class ImageLoader;
class GameObject;

class Animator
{
public:
	Animator(GameObject* object);
	~Animator();

private:
	GameObject* m_pObject;

	// ��������Ʈ�� ��µǴ� �ð�
	float m_FlowTime; 

	// ��������Ʈ�� �󸶵��� ����� �������� ���� �ð�
	float m_DelayTime;

	// �׷����� ��������Ʈ�� �ε��� 
	int m_CurrentIndex;

	// �ִϸ��̼��� �ǿ��� �ϴ� ��
	int m_FrameNum;

	// ��������Ʈ ��Ʈ ���� ��ġ
	HBVector2<float> m_PosInSheet;

public:
	
	// void PlayAni(int _sheetIndex, D2D1::Matrix3x2F _viewTM);

	HBVector2<float> GetPosInSheet() const { return m_PosInSheet; }
};

