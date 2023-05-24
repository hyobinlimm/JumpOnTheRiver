// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"

#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>		// WIC

// effect를 사용해보자 
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <d2d1effects_2.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "Windowscodecs.lib")

#pragma comment(lib, "dxguid.lib")

#include "ImageLoader.h"
#include "HBVector2.h"

//#pragma warning(disable:4244)

template<class T > void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}
#endif //PCH_H

// bitmap 이미지를 로드하기 위해 필요한 것
// 이미지의 주소??(그건 잘 모르겟지만 bitmap은 아님)가 위치한 메모리의 핸들
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

// 출력창에 출력하기 위한 것
#define TR(s){CString str;str.Format(L"%s", _T(s));OutputDebugString(str);}