#include "IntroCutScene2.h"
#include <windows.h>

IntroCutScene2::IntroCutScene2()
{
}

IntroCutScene2::~IntroCutScene2()
{
}

void IntroCutScene2::Initialize()
{
	m_ID = OBJECT_TYPE::background_startCutScene2;

	m_SmartKeyInput.Initialize();
}

void IntroCutScene2::Update()
{
	m_SmartKeyInput.Update();

	if (m_SmartKeyInput.IsKeyJustUp(VK_SPACE) == true)
	{
		Scene::S_pSceneManager->ChangeScene(SCENESTATEALL::INTRO_CUTSCENE3);
	}
}

void IntroCutScene2::Draw()
{
	S_pSceneManager->m_pEngine2D->DrawSprite((int)m_ID, 0, 960, 540);
}

void IntroCutScene2::Release()
{
}
