#include "Scene.h"
#include "DesireD2D.h"
#include "SceneManager.h"


SceneManager* Scene::S_pSceneManager = nullptr;

Scene::Scene()
	:m_pObjectManager(nullptr), m_NowSceneState(NOWSCENESTATE::FADE_OUT), m_IsGameEnd(false)
{

}

Scene::~Scene()
{

}

void Scene::Initialize()
{

}

void Scene::Draw()
{

}

void Scene::Release()
{

}
