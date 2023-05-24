#include "SceneManager.h"
#include "Define.h"
#include "TitleScene.h"
#include "OutroCredit.h"
#include "OutroEnding1.h"
#include "OutroEnding2.h"
#include "OutroEnding3.h"
#include "IntroCutScene1.h"
#include "IntroCutScene2.h"
#include "IntroCutScene3.h"
#include "IngameScene.h"
#include "Scene.h"
#include "CInput.h"

/// <summary>
/// static 멤버 변수 초기화
/// </summary>

SCENESTATEALL SceneManager::SceneState = SCENESTATEALL::INTRO_TITLE;		// 게임 첫 시작 State 는 게임타이틀 화면
Scene* SceneManager::pNowScene = nullptr;
bool SceneManager::IsSceneEnd = false;
float SceneManager::Opacity = 0;
bool SceneManager::IsFadeInEnd = false;
bool SceneManager::IsFadeOutEnd = false;
float SceneManager::FadeInFadeOutTime = 0;
ID2D1Bitmap* SceneManager::BlackScreen = nullptr;


SceneManager::SceneManager(DesireD2D* pEngine2D, ObjectManager* pObjectManager, SpriteManager* pSpriteManager, CInput* pInGameKeyInput)
	: m_pEngine2D(pEngine2D), m_pObjectManager(pObjectManager), m_pSpriteManager(pSpriteManager), m_pInGameKeyInput(pInGameKeyInput)
	, m_pCurrentScene(nullptr), m_isSpacebar(false)
{
	Scene::S_pSceneManager = this;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	// 타이틀 씬을 만들어주자. 
	TitleScene* _titleScene = new TitleScene();
	_titleScene->Initialize();
	m_Scenes.push_back(_titleScene);

	IntroCutScene1* _introCutScene1 = new IntroCutScene1();
	_introCutScene1->Initialize();
	m_Scenes.push_back(_introCutScene1);

	IntroCutScene2* _introCutScene2 = new IntroCutScene2();
	_introCutScene2->Initialize();
	m_Scenes.push_back(_introCutScene2);

	IntroCutScene3* _introCutScene3 = new IntroCutScene3();
	_introCutScene3->Initialize();
	m_Scenes.push_back(_introCutScene3);

	IngameScene* _ingameScene = new IngameScene();
	_ingameScene->Initialize();
	m_Scenes.push_back(_ingameScene);

	OutroEnding1* _outroEnding1 = new OutroEnding1();
	_outroEnding1->Initialize();
	m_Scenes.push_back(_outroEnding1);

	OutroEnding2* _outroEnding2 = new OutroEnding2();
	_outroEnding2->Initialize();
	m_Scenes.push_back(_outroEnding2);

	OutroEnding3* _outroEnding3 = new OutroEnding3();
	_outroEnding3->Initialize();
	m_Scenes.push_back(_outroEnding3);

	OutroCredit* _outroCredit = new OutroCredit();
	_outroCredit->Initialize();
	m_Scenes.push_back(_outroCredit);

	pNowScene = m_Scenes.at(0);
}

void SceneManager::Update()
{
	if (pNowScene)
	{
		pNowScene->Update();
	}
}

void SceneManager::Render()
{
	if (pNowScene)
	{
		pNowScene->Draw();
	}
}

void SceneManager::Release()
{
	if (pNowScene)
	{
		pNowScene->Release();
	}
}

void SceneManager::ChangeScene(SCENESTATEALL nextScene)
{
	if (SceneState != nextScene)
	{
		IsFadeOutEnd = false;

		// 기존 씬 삭제(safe delete)
		if (pNowScene)
		{
			pNowScene->Release();
			delete pNowScene;

			// 삭제 후 nullptr로 초기화
			pNowScene = nullptr;
		}

		switch (nextScene)
		{
		case SCENESTATEALL::INTRO_TITLE:
		{	
			// 인트로 타이틀 실행
			pNowScene = m_Scenes.at((int)SCENESTATEALL::INTRO_TITLE);
			//pNowScene = new TitleScene();
			//pNowScene->Initialize();
		}
			break;
		case SCENESTATEALL::INTRO_CUTSCENE1:
		{
			// 인트로 컷씬 실행
			pNowScene = m_Scenes.at((int)SCENESTATEALL::INTRO_CUTSCENE1);
			//pNowScene = new IntroCutScene1();
			//pNowScene->Initialize();
			SceneState = nextScene;
		}
			break;
		case SCENESTATEALL::INTRO_CUTSCENE2:
		{
			// 인트로 컷씬 실행
			pNowScene = m_Scenes.at((int)SCENESTATEALL::INTRO_CUTSCENE2);
			SceneState = nextScene;
		}
			break;
		case SCENESTATEALL::INTRO_CUTSCENE3:
		{
			// 인트로 컷씬 실행
			pNowScene = m_Scenes.at((int)SCENESTATEALL::INTRO_CUTSCENE3);
			SceneState = nextScene;
		}
			break;
		case SCENESTATEALL::INGAME_SCENE:
		{
			pNowScene = m_Scenes.at((int)SCENESTATEALL::INGAME_SCENE);
			SceneState = nextScene;
		}
			break;
		case SCENESTATEALL::OUTRO_ENDING1:
		{
			pNowScene = new OutroEnding1();
			pNowScene->Initialize();
			SceneState = nextScene;
		}
			break;
		case SCENESTATEALL::OUTRO_ENDING2:
		{
			pNowScene = new OutroEnding2();
			pNowScene->Initialize();
			SceneState = nextScene;
		}
			break;
		case SCENESTATEALL::OUTRO_ENDING3:
		{
			pNowScene = new OutroEnding3();
			pNowScene->Initialize();
			SceneState = nextScene;
		}
			break;
		case SCENESTATEALL::OUTRO_CREDIT:
		{
			pNowScene = new OutroCredit();
			pNowScene->Initialize();
			SceneState = nextScene;
		}
			break;
		}
	}
}

void SceneManager::LoadScene(int sceneIndex)
{

}

void SceneManager::FadeIn(float dTime)
{
	FadeInFadeOutTime += dTime * 30;

	if (FadeInFadeOutTime >= 1)
	{
		FadeInFadeOutTime = 0;

		if (Opacity < 1.0f && IsFadeInEnd == false)
			Opacity += 0.05f;
		else
			IsFadeInEnd = true;
	}
}

void SceneManager::FadeOut(float dTime)
{
	FadeInFadeOutTime += dTime * 30;

	if (FadeInFadeOutTime >= 1)
	{
		FadeInFadeOutTime = 0;

		if (IsFadeInEnd)
			Opacity -= 0.05f;

		if (Opacity <= 0)
		{
			Opacity = 0;
			IsFadeOutEnd = true;
			IsFadeInEnd = false;
		}
	}
}

void SceneManager::DrawBlackScreen()
{

}
