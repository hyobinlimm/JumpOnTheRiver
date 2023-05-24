#pragma once

#include "IScene.h"
#include "SpriteManager.h"
#include "Define.h"

class ObjectManager;
class SpriteManager;
class SceneManager;


/// <summary>
/// 인게임 씬
/// 
/// 오브젝트 매니저를 가지고 있으며, 인게임 진행을 담당한다.
/// </summary>
/// 

enum class SCENESTATEALL
{
	INTRO_TITLE,
	INTRO_CUTSCENE1,
	INTRO_CUTSCENE2,
	INTRO_CUTSCENE3,
	INGAME_SCENE,
	OUTRO_ENDING1,
	OUTRO_ENDING2,
	OUTRO_ENDING3,
	OUTRO_CREDIT,
	NONE
};

// 모든 씬의 상태(더 있으면 추가하기)
enum class NOWSCENESTATE
{
	NONE,
	FADE_OUT,
	GO_TO_NEXT_SCENE,
	GO_TO_PREV_SCENE,

};

class Scene : public IScene
{
public:
	Scene();
	~Scene();

	// IScene Interface
	//virtual void Update(float dTime) override;
	// 초기화
	virtual void Initialize();
	//virtual void Draw();
	virtual void Draw();
	//virtual void ShowDebug();
	virtual void Release();

private:
	DesireD2D* m_pEngine2D;
	ObjectManager* m_pObjectManager;
	SpriteManager* m_pSpriteManager;

	NOWSCENESTATE m_NowSceneState;

	bool m_IsGameEnd;

public:
	OBJECT_TYPE m_ID;

public:
	//bool isSpaceFbar;
	void SetIsGameEnd(bool val) { m_IsGameEnd = val; }
	void SetNowSceneState(NOWSCENESTATE val) { m_NowSceneState = val; }

public:
	static SceneManager* S_pSceneManager;
};

