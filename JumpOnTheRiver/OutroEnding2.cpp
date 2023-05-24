#include "OutroEnding2.h"
#include <windows.h>

OutroEnding2::OutroEnding2()
{
}

OutroEnding2::~OutroEnding2()
{
}

void OutroEnding2::Initialize()
{
	m_ID = OBJECT_TYPE::background_endingCutScene2;
}

void OutroEnding2::Update()
{

}

void OutroEnding2::Draw()
{
	S_pSceneManager->m_pEngine2D->DrawSprite((int)m_ID, 0, 960, 540);
}

void OutroEnding2::Release()
{
}
