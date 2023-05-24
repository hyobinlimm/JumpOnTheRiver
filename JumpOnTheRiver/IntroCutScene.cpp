#include "IntroCutScene.h"
#include <windows.h>

IntroCutScene::IntroCutScene()
	:m_pBackGround(nullptr), m_pObjectManager(nullptr)
{
}

IntroCutScene::~IntroCutScene()
{
}

void IntroCutScene::Initialize()
{
	Scene::Initialize();

	m_pBackGround->SpriteLoad();
}

void IntroCutScene::Update(float dTime)
{

}

void IntroCutScene::Draw(DesireD2D* engine2D)
{
	m_pObjectManager->Render();
}

void IntroCutScene::Release()
{
}
