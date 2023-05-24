// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include "GameProcess.h"

// 전역 변수:

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_crtBreakAlloc = 902;

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    GameProcess* mGameProcess = new GameProcess();

    
    // 애플리케이션 초기화를 수행합니다:
    if (!mGameProcess->Initialize(hInstance))
    {
        return FALSE;
    }

    mGameProcess->GameLoop();
    
    //_CrtDumpMemoryLeaks();

     delete mGameProcess; 
    mGameProcess = nullptr;

    return true;

}


