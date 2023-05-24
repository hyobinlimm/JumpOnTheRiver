#include "EndScene.h"
#include <windows.h>

EndScene::EndScene()
	:m_pBackGround(nullptr), m_pObjectManager(nullptr)
{
}

EndScene::~EndScene()
{
}

void EndScene::Initialize()
{
	Scene::Initialize();

	m_pBackGround->SpriteLoad();
}

void EndScene::Update(float dTime)
{

}

void EndScene::Draw(DesireD2D* engine2D)
{
	m_pObjectManager->Render();
}

void EndScene::Release()
{
}
