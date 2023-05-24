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
/// ������ ����
/// 
/// �����丵��
/// �ʱ�ȭ, �Ҹ�, ���ѷ����� ���� (Update/Render) => O
/// ĳ������ ����, Ű �Է��� ��ü���� �κ� => X
/// 
/// 2022.02.21 LeHideHome
/// </summary>
class GameProcess
{
public:
	GameProcess();
	~GameProcess();
	
	// �ܺο��� ���� �����ϵ��� �ϴ� �Լ�
public:
	bool Initialize(HINSTANCE hInstance);
	void GameLoop();

	void CreateScene();

	// Initialzie
private:
	HWND InitWin32(HINSTANCE hInstance);	// ������ �ʱ�ȭ�ϰ�, ������ �ڵ��� �����Ѵ�.

	// GameLoop
private:
	void UpdateAll();
	void RenderAll();

	// Win32�� �ݹ��Լ�
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	static DesireD2D* s_pEngine2D;

private:
	// Win32����
	HWND m_hWnd;

	// 2D���� ����
	DesireD2D* m_pEngine2D;

	// �ΰ��� ����
	ObjectManager* m_pObjectManager;
	SceneManager* m_pSceneManager;
	HBTime* m_pTimer;

	CInput* m_KeyInput;

	// ���ҽ� ����
	SpriteManager* m_pSpriteManager;
};

