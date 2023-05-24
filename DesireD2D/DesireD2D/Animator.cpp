#include "pch.h"
#include "Animator.h"
#include "ImageLoader.h"
#include "HBSprite.h"
#include "HBTime.h"

Animator::Animator(GameObject* object)
	: m_pObject(object), m_FlowTime(0.0), m_DelayTime(0.5), m_CurrentIndex(0), m_FrameNum(0),
	m_PosInSheet({ 0,0 })
{

}

Animator::~Animator()
{
	// 불완전한 형식 'GameObject'에 대한 포인터를 섹제했습니다. 소멸자가 호출되지 않습니다.
	// 란 경고가 뜸. 무슨 의미이지? GameObject가 animator를 먼저 소멸시키나?  
	//if (m_pObject != nullptr)
	//{
	//	delete m_pObject;
	//}

	m_FlowTime = NULL;
	m_DelayTime = NULL;
	m_CurrentIndex = NULL;
	m_FrameNum = NULL;
}

/*
void Animator::PlayAni(int _sheetIndex, D2D1::Matrix3x2F _viewTM)
{
	// m_SpriteInfos에 들어있는 이미지를 가져옴.
	HBSpriteSheet* _spriteSheet = ImageLoader::GetInstance()->GetSpriteSheetInfo(_sheetIndex);
	HBSprite* _sprite = _spriteSheet->m_Sprites.at(m_CurrentIndex);

	// 현재 sheet에서 어디를 중점으로 그리고 있는지 그 위치를 가져오자. 
	m_PosInSheet.m_x = _sprite->width / 2;
	m_PosInSheet.m_y = _sprite->height / 2;

	// 애니메이션 시간에 현재 deltaTime를 받아온다. 
	m_FlowTime += HBTime::GetInstance()->GetDeltaTime();

	// m_FlowTime은 시작시간이 0초부터 시작하기 때문에 
	// m_DDelayTime 보다 작을 수 밖에 없음. 
	// m_flowTime이 m_DelayTime 보다 커지는 순간 m_CurrentIndex++ 해줌.
	if (m_DelayTime <= m_FlowTime)
	{
		// m_CurrentIndex++ 하여 m_FrameCount를 보다 커졌을때, 
		// 나머지 연산자를 통해 다시 0으로 되돌려줌. 
		m_CurrentIndex = (m_CurrentIndex + 1) % _spriteSheet->m_FrameCount;

		// 현재시간을 0으로 만듦
		m_FlowTime = 0.f;
	}

	// _spriteIndex를 변화된 m_CurrentIndex로 바꿔줌.
	m_CurrentIndex = m_CurrentIndex;

	/// 싱글턴의 악몽...
	// 바뀐 m_CurrentIndex를 인자로 넣어서 그려주자.
	DrawSprite(m_pObject, _sheetIndex, m_CurrentIndex, _viewTM);
}
*/
