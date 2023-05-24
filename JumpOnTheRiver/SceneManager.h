#pragma once

#include <vector>
#include "DesireD2D.h"
#include "Scene.h"

class IScene;
class DesireD2D;
class CInput;

/// <summary>
/// 씬들을 내부적으로 가지고 있고, 업데이트와 렌더를 한다.
/// </summary>
class SceneManager
{
public:
	SceneManager(DesireD2D* pEngine2D, ObjectManager* pObjectManager, SpriteManager* pSpriteManager, CInput* pInGameKeyInput);
	~SceneManager();

private:
	std::vector<Scene*> m_Scenes;

	IScene* m_pCurrentScene;	// 현재씬

public:
	static SCENESTATEALL SceneState;
	static Scene* pNowScene;

public:
	DesireD2D* m_pEngine2D;
	ObjectManager* m_pObjectManager;
	SpriteManager* m_pSpriteManager;
	CInput* m_pInGameKeyInput;
	

public:
	// 현재 씬 상태
	//static SCENE_TYPE SceneState;
	
	// Scene 생성
	void Initialize();
	void Update();
	void Render();
	void Release();

	// 씬을 전환하는 스택틱 함수
	// 비정적 클래스를 사용하되, 특정 함수만 전역성을 보장받기 위함
	void ChangeScene(SCENESTATEALL nextScene);

	// Scene 로드
	void LoadScene(int sceneIndex);

public:
	bool m_isSpacebar;

	// FadeInFadeOut
	static float Opacity;
	static float FadeInFadeOutTime;
	static bool IsFadeInEnd;
	static bool IsFadeOutEnd;
	static bool IsSceneEnd;

	// 엔진에서 가져올 것. 
	static ID2D1Bitmap* BlackScreen;

	static void FadeIn(float dTime);
	static void FadeOut(float dTime);

	static void DrawBlackScreen();
};


