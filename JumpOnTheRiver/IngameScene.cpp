#include "IngameScene.h"
#include <windows.h>
#include "CInput.h"
#include "ObjectManager.h"



IngameScene::IngameScene()
{
}

IngameScene::~IngameScene()
{
}

void IngameScene::Initialize()
{
	// �Է��� ����ϴ� Ŭ���� �ʱ�ȭ
	m_KeyInput = S_pSceneManager->m_pInGameKeyInput;

	// ������Ʈ �Ŵ��� �ʱ�ȭ �� ����
	m_pObjectManager = S_pSceneManager->m_pObjectManager;

	m_pEngine2D = S_pSceneManager->m_pEngine2D;
}

void IngameScene::Update()
{
	// Ű �Է��� ����
	m_KeyInput->GetKeyInput();

	// �� ������Ʈ���� ������Ʈ
	m_pObjectManager->Update();
}

void IngameScene::Draw()
{
	//engine2D->DrawSprite((int)m_ID, 0, 960, 540);
	m_pObjectManager->Render();
}

void IngameScene::Release()
{
}
