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
	// �ҿ����� ���� 'GameObject'�� ���� �����͸� �����߽��ϴ�. �Ҹ��ڰ� ȣ����� �ʽ��ϴ�.
	// �� ��� ��. ���� �ǹ�����? GameObject�� animator�� ���� �Ҹ��Ű��?  
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
	// m_SpriteInfos�� ����ִ� �̹����� ������.
	HBSpriteSheet* _spriteSheet = ImageLoader::GetInstance()->GetSpriteSheetInfo(_sheetIndex);
	HBSprite* _sprite = _spriteSheet->m_Sprites.at(m_CurrentIndex);

	// ���� sheet���� ��� �������� �׸��� �ִ��� �� ��ġ�� ��������. 
	m_PosInSheet.m_x = _sprite->width / 2;
	m_PosInSheet.m_y = _sprite->height / 2;

	// �ִϸ��̼� �ð��� ���� deltaTime�� �޾ƿ´�. 
	m_FlowTime += HBTime::GetInstance()->GetDeltaTime();

	// m_FlowTime�� ���۽ð��� 0�ʺ��� �����ϱ� ������ 
	// m_DDelayTime ���� ���� �� �ۿ� ����. 
	// m_flowTime�� m_DelayTime ���� Ŀ���� ���� m_CurrentIndex++ ����.
	if (m_DelayTime <= m_FlowTime)
	{
		// m_CurrentIndex++ �Ͽ� m_FrameCount�� ���� Ŀ������, 
		// ������ �����ڸ� ���� �ٽ� 0���� �ǵ�����. 
		m_CurrentIndex = (m_CurrentIndex + 1) % _spriteSheet->m_FrameCount;

		// ����ð��� 0���� ����
		m_FlowTime = 0.f;
	}

	// _spriteIndex�� ��ȭ�� m_CurrentIndex�� �ٲ���.
	m_CurrentIndex = m_CurrentIndex;

	/// �̱����� �Ǹ�...
	// �ٲ� m_CurrentIndex�� ���ڷ� �־ �׷�����.
	DrawSprite(m_pObject, _sheetIndex, m_CurrentIndex, _viewTM);
}
*/
