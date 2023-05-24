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

/// 게임 진행에 필요한 각 클래스들을 초기화함
bool GameProcess::Initialize(HINSTANCE hInstance)
{
	// 그래픽스 엔진 초기화
	m_pEngine2D = new DesireD2D();
	s_pEngine2D = m_pEngine2D;

	// 입력을 담당하는 클래스 초기화
	m_KeyInput = new CInput();

	// 윈도 클래스를 등록 / 윈도 창을 생성
	HWND _hWnd = InitWin32(hInstance);

	if (!_hWnd) return FALSE;

	m_hWnd = _hWnd;

	// 2D 그래픽스 엔진 초기화 및 factory 생성
	m_pEngine2D->Initialize(_hWnd);

	// 시간을 담당하는 클래스
	HBTime::GetInstance()->Initialize();

	/// 리소스와 오브젝트
	// 필요한 이미지 초기화 
	m_pSpriteManager = new SpriteManager(m_pEngine2D);	/// 리소스 매니저 안쪽으로 들어가야 할 것 같기는 한데..
	m_pSpriteManager->SpriteLoad();

	// 오브젝트 매니저 초기화 및 생성
	m_pObjectManager = new ObjectManager();

	// 씬 매니저 생성 및 초기화
	m_pSceneManager = new SceneManager(m_pEngine2D, m_pObjectManager, m_pSpriteManager, m_KeyInput);
	m_pSceneManager->Initialize();

	
	//// 오브젝트의 데이터를 로드합니다.
	m_pObjectManager->Initialize(m_pEngine2D, m_KeyInput);


	/// 싱글턴들 초기화

#pragma region 사운드매니저는 리소스매니저가 있는 경우 그쪽으로 가야 한다.

	// SoundManager 초기화
	SoundManager::GetInstance()->Initialize(5);

	// 사운드 리소스들을 로드한다.
	SoundManager::GetInstance()->LoadSoundFile(_T("../JumpOnTheRiver/Data"));
	//SoundManager::GetInstance()->VolumeUp(3);				// 볼륨 크게
	SoundManager::GetInstance()->Play(0, L"MainStage");		// BGM사운드

#pragma endregion 


	return TRUE;
}

void GameProcess::GameLoop()
{
	MSG msg;

	// 기본 메시지 루프입니다:
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

/// 윈도를 초기화하고, 윈도의 핸들을 리턴한다.
HWND GameProcess::InitWin32(HINSTANCE hInstance)
{
	HWND _hWnd = nullptr;

	WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_JUMPONTHERIVER, szWindowClass, MAX_LOADSTRING);

	/// 윈도우 창 등록
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

	/// 인스턴스 핸들을 저장하고 주 창을 만듦. 
	_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, SCRWIDTH, SCRHEIGHT, nullptr, nullptr, hInstance, nullptr);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JUMPONTHERIVER));

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);

	return _hWnd;
}

void GameProcess::UpdateAll()
{
	// 사운드매니저 업데이트
	SoundManager::GetInstance()->Update();

	// 시간을 업데이트
	HBTime::GetInstance()->Update();

	m_pSceneManager->Update();
	
	// 키 입력을 받음
	//m_KeyInput->GetKeyInput();

	// 각 오브젝트들의 업데이트
	//m_pObjectManager->Update();

	//  씬 메니저 업데이트

	// 어떤 이유로 렌더타겟이 없어지면, 다시 만든다.
	m_pEngine2D->OnDeviceLost();

	/// 그래픽스 엔진 쪽으로 카메라 정보(viewTM을 전달해준다)
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
       	// 씬 메니저의 상태를 INTRO로 초기화
	m_pSceneManager->ChangeScene(SCENESTATEALL::INTRO_TITLE);
}

LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);

			// 메뉴 선택을 구문 분석합니다:
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
			// 창 크기 변경 때 호출
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

