#include "GameProcess.h"
#include "Player.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "HBTime.h"
#include "BackGround.h"
#include "Define.h"



DesireD2D* GameProcess::s_pEngine2D = nullptr;

GameProcess::GameProcess()
	: m_hWnd(nullptr), m_pEngine2D(nullptr), 
	m_pObjectManager(nullptr), m_pSceneManager(nullptr), m_KeyInput(nullptr)
	, m_pSpriteManager(nullptr)
{

}

GameProcess::~GameProcess()
{
	delete m_pSpriteManager;
	delete m_pObjectManager;
	delete m_KeyInput;

	SoundManager::GetInstance()->Release();
	//delete m_pEngine2D;
}

/// ���� ���࿡ �ʿ��� �� Ŭ�������� �ʱ�ȭ��
bool GameProcess::Initialize(HINSTANCE hInstance)
{
	// �׷��Ƚ� ���� �ʱ�ȭ
	m_pEngine2D = new DesireD2D();
	s_pEngine2D = m_pEngine2D;

	// �Է��� ����ϴ� Ŭ���� �ʱ�ȭ
	m_KeyInput = new CInput();

	// ���� Ŭ������ ��� / ���� â�� ����
	HWND _hWnd = InitWin32(hInstance);

	if (!_hWnd) return FALSE;

	m_hWnd = _hWnd;

	// 2D �׷��Ƚ� ���� �ʱ�ȭ �� factory ����
	m_pEngine2D->Initialize(_hWnd);

	// �ð��� ����ϴ� Ŭ����
	HBTime::GetInstance()->Initialize();

	/// ���ҽ��� ������Ʈ
	// �ʿ��� �̹��� �ʱ�ȭ 
	m_pSpriteManager = new SpriteManager(m_pEngine2D);	/// ���ҽ� �Ŵ��� �������� ���� �� �� ����� �ѵ�..
	m_pSpriteManager->SpriteLoad();

	// ������Ʈ �Ŵ��� �ʱ�ȭ �� ����
	m_pObjectManager = new ObjectManager();

	// �� �Ŵ��� ���� �� �ʱ�ȭ
	m_pSceneManager = new SceneManager(m_pEngine2D, m_pObjectManager, m_pSpriteManager, m_KeyInput);
	m_pSceneManager->Initialize();

	
	//// ������Ʈ�� �����͸� �ε��մϴ�.
	m_pObjectManager->Initialize(m_pEngine2D, m_KeyInput);


	/// �̱��ϵ� �ʱ�ȭ

#pragma region ����Ŵ����� ���ҽ��Ŵ����� �ִ� ��� �������� ���� �Ѵ�.

	// SoundManager �ʱ�ȭ
	SoundManager::GetInstance()->Initialize(5);

	// ���� ���ҽ����� �ε��Ѵ�.
	SoundManager::GetInstance()->LoadSoundFile(_T("../JumpOnTheRiver/Data"));
	//SoundManager::GetInstance()->VolumeUp(3);				// ���� ũ��
	SoundManager::GetInstance()->Play(0, L"MainStage");		// BGM����

#pragma endregion 


	return TRUE;
}

void GameProcess::GameLoop()
{
	MSG msg;

	// �⺻ �޽��� �����Դϴ�:
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			UpdateAll();

			RenderAll();
		}
	}
}

/// ������ �ʱ�ȭ�ϰ�, ������ �ڵ��� �����Ѵ�.
HWND GameProcess::InitWin32(HINSTANCE hInstance)
{
	HWND _hWnd = nullptr;

	WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_JUMPONTHERIVER, szWindowClass, MAX_LOADSTRING);

	/// ������ â ���
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_JUMPONTHERIVER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_JUMPONTHERIVER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);

	/// �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����. 
	_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, SCRWIDTH, SCRHEIGHT, nullptr, nullptr, hInstance, nullptr);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JUMPONTHERIVER));

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);

	return _hWnd;
}

void GameProcess::UpdateAll()
{
	// ����Ŵ��� ������Ʈ
	SoundManager::GetInstance()->Update();

	// �ð��� ������Ʈ
	HBTime::GetInstance()->Update();

	m_pSceneManager->Update();
	
	// Ű �Է��� ����
	//m_KeyInput->GetKeyInput();

	// �� ������Ʈ���� ������Ʈ
	//m_pObjectManager->Update();

	//  �� �޴��� ������Ʈ

	// � ������ ����Ÿ���� ��������, �ٽ� �����.
	m_pEngine2D->OnDeviceLost();

	/// �׷��Ƚ� ���� ������ ī�޶� ����(viewTM�� �������ش�)
	m_pEngine2D->Update(m_pObjectManager->GetViewTM());
}

void GameProcess::RenderAll()
{
	m_pEngine2D->BeginRender();

	m_pSceneManager->Render();
	
	m_pEngine2D->EndRender();

}

void GameProcess::CreateScene()
{
       	// �� �޴����� ���¸� INTRO�� �ʱ�ȭ
	m_pSceneManager->ChangeScene(SCENESTATEALL::INTRO_TITLE);
}

LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);

			// �޴� ������ ���� �м��մϴ�:
			switch (wmId)
			{
				case IDM_EXIT:
				{
					DestroyWindow(hWnd);
				}
				break;
			}
		}
		break;

		case WM_SIZE:
		{
			// â ũ�� ���� �� ȣ��
			s_pEngine2D->OnDeviceLost();
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	return 0;
}

