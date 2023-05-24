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
	// 입력을 담당하는 클래스 초기화
	m_KeyInput = S_pSceneManager->m_pInGameKeyInput;

	// 오브젝트 매니저 초기화 및 생성
	m_pObjectManager = S_pSceneManager->m_pObjectManager;

	m_pEngine2D = S_pSceneManager->m_pEngine2D;
}

void IngameScene::Update()
{
	// 키 입력을 받음
	m_KeyInput->GetKeyInput();

	// 각 오브젝트들의 업데이트
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
