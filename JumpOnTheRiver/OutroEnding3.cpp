#include "OutroEnding3.h"
#include <windows.h>

OutroEnding3::OutroEnding3()
{
}

OutroEnding3::~OutroEnding3()
{
}

void OutroEnding3::Initialize()
{
	m_ID = OBJECT_TYPE::background_endingCutScene3;
}

void OutroEnding3::Update()
{

}

void OutroEnding3::Draw()
{
	S_pSceneManager->m_pEngine2D->DrawSprite((int)m_ID, 0, 960, 540);
}

void OutroEnding3::Release()
{
}
