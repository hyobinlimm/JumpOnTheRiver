#pragma once
#include "framework.h"
#include "Resource.h"
#include "DesireD2D.h"
#include "CInput.h"

#pragma comment(lib, "DesireD2D.lib")

class ObjectManager;
class SceneManager;
class SpriteManager;
class Player;
class Object;
class BackGround;
class Camera;
class HBTime;

/// <summary>
/// 게임의 진행
/// 
/// 리팩토링중
/// 초기화, 소멸, 무한루프를 도는 (Update/Render) => O
/// 캐릭터의 점프, 키 입력의 구체적인 부분 => X
/// 
/// 2022.02.21 LeHideHome
/// </summary>
class GameProcess
{
public:
	GameProcess();
	~GameProcess();
	
	// 외부에서 접근 가능하도록 하는 함수
public:
	bool Initialize(HINSTANCE hInstance);
	void GameLoop();

	void CreateScene();

	// Initialzie
private:
	HWND InitWin32(HINSTANCE hInstance);	// 윈도를 초기화하고, 윈도의 핸들을 리턴한다.

	// GameLoop
private:
	void UpdateAll();
	void RenderAll();

	// Win32의 콜백함수
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	static DesireD2D* s_pEngine2D;

private:
	// Win32관련
	HWND m_hWnd;

	// 2D엔진 관련
	DesireD2D* m_pEngine2D;

	// 인게임 관련
	ObjectManager* m_pObjectManager;
	SceneManager* m_pSceneManager;
	HBTime* m_pTimer;

	CInput* m_KeyInput;

	// 리소스 관련
	SpriteManager* m_pSpriteManager;
};

