#include "IntroCutScene3.h"
#include <windows.h>

IntroCutScene3::IntroCutScene3()
{
}

IntroCutScene3::~IntroCutScene3()
{
}

void IntroCutScene3::Initialize()
{
	m_ID = OBJECT_TYPE::background_startCutScene3;
	m_SmartKeyInput.Initialize();
}

void IntroCutScene3::Update()
{
	m_SmartKeyInput.Update();

	if (m_SmartKeyInput.IsKeyJustUp(VK_SPACE) == true)
	{
		S_pSceneManager->ChangeScene(SCENESTATEALL::INGAME_SCENE);
	}
}

void IntroCutScene3::Draw()
{
	S_pSceneManager->m_pEngine2D->DrawSprite((int)m_ID, 0, 960, 540);
}

void IntroCutScene3::Release()
{
}
