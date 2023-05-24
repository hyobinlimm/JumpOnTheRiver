#include "OutroEnding.h"
#include <windows.h>

OutroEnding::OutroEnding()
	:m_pBackGround(nullptr), m_pObjectManager(nullptr)
{
}

OutroEnding::~OutroEnding()
{
}

void OutroEnding::Initialize()
{
	Scene::Initialize();

	m_pBackGround->SpriteLoad();
}

void OutroEnding::Update(float dTime)
{

}

void OutroEnding::Draw(DesireD2D* engine2D)
{
	m_pObjectManager->Render();
}

void OutroEnding::Release()
{
}
