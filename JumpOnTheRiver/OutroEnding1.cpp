#include "OutroEnding1.h"
#include <windows.h>

OutroEnding1::OutroEnding1()
{
}

OutroEnding1::~OutroEnding1()
{
}

void OutroEnding1::Initialize()
{
	m_ID = OBJECT_TYPE::background_endingCutScene1;
}

void OutroEnding1::Update()
{

}

void OutroEnding1::Draw()
{
	S_pSceneManager->m_pEngine2D->DrawSprite((int)m_ID, 0, 960, 540);
}

void OutroEnding1::Release()
{
}
