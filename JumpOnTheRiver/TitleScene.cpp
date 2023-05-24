#include "TitleScene.h"
#include <windows.h>

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	m_ID = OBJECT_TYPE::background_gameTitle;

	m_SmartKeyInput.Initialize();
}

void TitleScene::Update()
{
	// �ƹ�Ű�� �����ø� �ΰ��� ������ �Ѿ�ϴ�.
	//if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	//{
	//	SceneManager::GetInstance()->ChangeScene(SCENESTATEALL::INTRO_CUTSCENE1);
	//	isSpacebar = true;
	//}

	m_SmartKeyInput.Update();

	// SPACE�� ������ ���� ������ �ΰ��� ������ �Ѿ�ϴ�.
	if (m_SmartKeyInput.IsKeyJustUp(VK_SPACE) == true)
	{
		Scene::S_pSceneManager->ChangeScene(SCENESTATEALL::INTRO_CUTSCENE1);
	}
}

void TitleScene::Draw()
{
	S_pSceneManager->m_pEngine2D->DrawSprite((int)m_ID, 0, 960, 540);
}

void TitleScene::Release()
{
}
