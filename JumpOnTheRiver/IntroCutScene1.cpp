#include "IntroCutScene1.h"
#include <windows.h>

IntroCutScene1::IntroCutScene1()
{
}

IntroCutScene1::~IntroCutScene1()
{
}

void IntroCutScene1::Initialize()
{
	m_ID = OBJECT_TYPE::background_startCutScene1;

	m_SmartKeyInput.Initialize();
}

void IntroCutScene1::Update()
{
	m_SmartKeyInput.Update();

	if (m_SmartKeyInput.IsKeyJustUp(VK_SPACE) == true)
	{
		S_pSceneManager->ChangeScene(SCENESTATEALL::INTRO_CUTSCENE2);
	}
}

void IntroCutScene1::Draw()
{
	S_pSceneManager->m_pEngine2D->DrawSprite((int)m_ID, 0, 960, 540);
}

void IntroCutScene1::Release()
{
}
