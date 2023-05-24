#pragma once

#include <vector>
#include "DesireD2D.h"
#include "Scene.h"

class IScene;
class DesireD2D;
class CInput;

/// <summary>
/// ������ ���������� ������ �ְ�, ������Ʈ�� ������ �Ѵ�.
/// </summary>
class SceneManager
{
public:
	SceneManager(DesireD2D* pEngine2D, ObjectManager* pObjectManager, SpriteManager* pSpriteManager, CInput* pInGameKeyInput);
	~SceneManager();

private:
	std::vector<Scene*> m_Scenes;

	IScene* m_pCurrentScene;	// �����

public:
	static SCENESTATEALL SceneState;
	static Scene* pNowScene;

public:
	DesireD2D* m_pEngine2D;
	ObjectManager* m_pObjectManager;
	SpriteManager* m_pSpriteManager;
	CInput* m_pInGameKeyInput;
	

public:
	// ���� �� ����
	//static SCENE_TYPE SceneState;
	
	// Scene ����
	void Initialize();
	void Update();
	void Render();
	void Release();

	// ���� ��ȯ�ϴ� ����ƽ �Լ�
	// ������ Ŭ������ ����ϵ�, Ư�� �Լ��� �������� ����ޱ� ����
	void ChangeScene(SCENESTATEALL nextScene);

	// Scene �ε�
	void LoadScene(int sceneIndex);

public:
	bool m_isSpacebar;

	// FadeInFadeOut
	static float Opacity;
	static float FadeInFadeOutTime;
	static bool IsFadeInEnd;
	static bool IsFadeOutEnd;
	static bool IsSceneEnd;

	// �������� ������ ��. 
	static ID2D1Bitmap* BlackScreen;

	static void FadeIn(float dTime);
	static void FadeOut(float dTime);

	static void DrawBlackScreen();
};


