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

	// 스프라이트가 출력되는 시간
	float m_FlowTime; 

	// 스프라이트를 얼마동안 출력할 것인지에 대한 시간
	float m_DelayTime;

	// 그려지는 스프라이트의 인덱스 
	int m_CurrentIndex;

	// 애니메이션이 되여야 하는 수
	int m_FrameNum;

	// 스프라이트 시트 내의 위치
	HBVector2<float> m_PosInSheet;

public:
	
	// void PlayAni(int _sheetIndex, D2D1::Matrix3x2F _viewTM);

	HBVector2<float> GetPosInSheet() const { return m_PosInSheet; }
};

