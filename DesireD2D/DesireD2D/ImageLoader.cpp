#include "pch.h"
#include "ImageLoader.h"
#include "HBTime.h"
#include "HBSprite.h"
#include "GameObject.h"
#include "Transform.h"
#include "Shape.h"

ImageLoader::ImageLoader()
	: TemplateSingleton<ImageLoader>(),
	/*m_pWICFactory(nullptr), m_pConvertedSrcBmp(nullptr), m_pD2DBitmap(nullptr), m_pRenderTarget(nullptr),*/ 
	m_pShape(nullptr), 
	m_FlowTime(0.f), m_DelayTime(0.1f), m_CurrentIndex(0),
	m_SpriteCount(0), m_SpriteSheetCount(0), m_FrameNum(0)
{
}

ImageLoader::~ImageLoader()
{
	// DesireD2D에서 ImageLoader->Release()를 호출해준다. 
	// 굳이 여기서 한번 더 제거를 해야 하나? 
	// Release();
	DestroyInstance();
}

/*
HRESULT ImageLoader::CreateWICFactory(ID2D1HwndRenderTarget* pRenderTarget)
{
	HRESULT hr = S_OK;
	if (SUCCEEDED(hr))
	{
		// COM 초기화
		CoInitialize(NULL);

		// Create WIC factory.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&m_pWICFactory)
		);
	}

	m_pRenderTarget = pRenderTarget;

	return hr;
}*/


wchar_t* ImageLoader::ConvertCStoWCS(const char* orig)
{
	// wcstringd의 문자열 수
	size_t _NewSize = strlen(orig) + 1;

	// 문자열의 수 만큼 _WCString의 버퍼를 만들어 줌. 
	wchar_t* _WCString = new wchar_t[_NewSize];

	// char* 를 wchar_t*로 변환
	size_t _ConvertedChars = 0;
	mbstowcs_s(&_ConvertedChars, _WCString, _NewSize, orig, _TRUNCATE);

	return _WCString;
}

void ImageLoader::initialize(ID2D1HwndRenderTarget* pRenderTarget)
{
	m_pRenderTarget = pRenderTarget;
}

/*
int ImageLoader::LoadSpriteSheet(const char* filePath, int frameCount)
{
	// char 형의 주소를 wchar_t 형으로 바꿔주자. 
	wchar_t* _WCString = this->ConvertCStoWCS(filePath);

	// 이미지를 불러온다. 
	int _result = LoadSpriteSheet(_WCString, frameCount);

	// 포인터 변수 해제
	delete[] _WCString;

	return _result;
}*/

/*
int ImageLoader::LoadSpriteSheet(const wchar_t* filePath, int frameCount)
{
	HRESULT hr = S_OK;

	ID2D1Bitmap* pNewBitmap;

	hr = LoadBitmapFromFile(m_pRenderTarget, m_pWICFactory, filePath, 0, 0, &pNewBitmap);

	float _width = pNewBitmap->GetSize().width;
	float _height = pNewBitmap->GetSize().height;

	SpriteSheetInfo(pNewBitmap, (int)_width, (int)_height, frameCount);

	// 불러 온 비트맵 생성
	if (SUCCEEDED(hr))
	{
		m_SpriteSheetCount++;

		return (m_SpriteSheetCount - 1); // 넣어준 m_SpriteSheetCount를 +1를 해주었기 때문에 넣어준 m_SpriteSheetCount는 -1를 해줘야지 넣어준 sheet의 수를 알 수 있음. 
	}

	return -1; // 핸들이 없으면 오류 발생
}*/

/*
void ImageLoader::LoadImageResource(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	HRESULT hr = S_OK;

	if (SUCCEEDED(hr))
	{
		hr = LoadBitmapFromFile(m_pRenderTarget, m_pWICFactory, L"../DesireD2D/DesireD2D/Data/sheet.PNG", 300, 300, &m_pD2DBitmap);
	}

	if (SUCCEEDED(hr))
	{
		OutputDebugString(L"핸들 받아오기 성공^ㅁ^\n");
	}
	else
	{
		OutputDebugString(L"핸들 받아오기 실패8ㅁ8\n");
	}
}*/

/*
HBSpriteSheet* ImageLoader::SpriteSheetInfo(int index, int width, int highte, int frameCount)
{
	// 스프라이트 클래스 생성. 
	HBSpriteSheet* _newSpriteInfo = new HBSpriteSheet(index, width, highte, 0, 0, frameCount);

	// 생성된 스프라이트 정보를 m_SpriteInfos에 넣어준다. 
	m_SpriteSheetInfos.push_back(_newSpriteInfo);
	m_SpriteCount++;

	return _newSpriteInfo;
}*/

/*
void ImageLoader::SpriteSheetInfo(int width, int highte, int frameCount)
{
	// 스프라이트 클래스 생성. 
	HBSpriteSheet* _newSpriteInfo = new HBSpriteSheet(width, highte, 0, 0, frameCount);

	// 생성된 스프라이트 정보를 m_SpriteInfos에 넣어준다. 
	m_SpriteSheetInfos.push_back(_newSpriteInfo);
	m_SpriteCount++;
}*/

/*
void ImageLoader::SpriteSheetInfo(ID2D1Bitmap* Bitmap, int width, int height, int frameCount)
{
	// 스프라이트 클래스 생성. 
	HBSpriteSheet* _newSpriteInfo = new HBSpriteSheet(width, height, 0, 0, frameCount);

	_newSpriteInfo->m_pBitmapAddress = Bitmap;

	// 애니매이션이 있으면 frameCount만큼 자르고 스프라이트 벡터에 넣어주자. 
	if (frameCount != 0)
	{
		// 원본이미지를 프레임 수 만큼 자르자.
		int _offset = width / frameCount;
		int _y = 0;

		// 스프라이트 sheet를 가지고 왔을때 딱 한번 계산해 주면 됨. 
		// 중점에서부터 sprite의 크기
		_newSpriteInfo->m_ScrSize.m_x = _offset / 2.0f;
		_newSpriteInfo->m_ScrSize.m_y = height / 2.0f;


		for (int i = 0; i < frameCount; i++)
		{
			HBSprite* _newSprite = new HBSprite();
			_newSprite = SplitSpriteSheet(i * _offset, _y, (i + 1) * _offset, height);
			_newSpriteInfo->m_Sprites.push_back(_newSprite);
			m_SpriteCount++;
		}
	}
	else
	{	
		// 중점에서부터 sprite의 크기
		_newSpriteInfo->m_ScrSize.m_x = width / 2.0f;
		_newSpriteInfo->m_ScrSize.m_y = height / 2.0f;
		HBSprite* _newSprite = new HBSprite(0, 0, width, height);
		_newSpriteInfo->m_Sprites.push_back(_newSprite);
		m_SpriteCount++;
	}

	// 생성된 스프라이트 정보를 m_SpriteInfos에 넣어준다. 
	m_SpriteSheetInfos.push_back(_newSpriteInfo);
	m_SpriteCount++;

}*/

/*
HBSprite* ImageLoader::SplitSpriteSheet(int x, int y, int width, int height)
{
	HBSprite* _newSprite = new HBSprite(x, y, width, height);

	return _newSprite;
}*/

/*
void ImageLoader::DrawBitmap()
{
	D2D1_RECT_F pos;
	pos.left = 300;
	pos.top = 300;
	pos.right = 400;
	pos.bottom = 400;

	D2D1_SIZE_F originalSize = m_pD2DBitmap->GetSize();

	float customWidth = originalSize.width / 4;
	float customHeight = originalSize.height / 4;

	D2D1_RECT_F rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = customWidth;
	rect.bottom = customHeight;

	m_pRenderTarget->DrawBitmap(m_pD2DBitmap);
}
*/

/*
void ImageLoader::DrawSprite(int _sheetIndex, int _spriteIndex, int _posX, int _posY, D2D1::Matrix3x2F _viewTM)
{
	// m_SpriteInfos에 들어있는 이미지를 가져옴.
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(_sheetIndex);

	HBSprite* _sprite = _spriteSheet->m_Sprites.at(_spriteIndex);

	// 여기서 setTransform를 해주자. 그리기 전에 해야함. 
	m_pRenderTarget->SetTransform(_viewTM);

	if (_sprite != nullptr)
	{
		m_pRenderTarget->DrawBitmap(_spriteSheet->m_pBitmapAddress,
			D2D1::RectF((float)(_posX - _spriteSheet->m_ScrSize.m_x),
				(float)(_posY - _spriteSheet->m_ScrSize.m_y),
				(float)(_posX + _spriteSheet->m_ScrSize.m_x), 
				(float)(_posY + _spriteSheet->m_ScrSize.m_y)), // 화면에 위치하는 사각형의 크기? 좌표? 
			1.0f, // 불투명도 
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(_sprite->x, _sprite->y, _sprite->width, _sprite->height)); // sheet를 필요한 만큼 잘라낸 사각형 크기? 좌표  
	}
}*/

/*
void ImageLoader::DrawSprite(GameObject* _object, int _sheetIndex, int _spriteIndex, D2D1::Matrix3x2F _viewTM)
{
	// m_SpriteInfos에 들어있는 이미지를 가져옴.
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(_sheetIndex);

	HBSprite* _sprite = _spriteSheet->m_Sprites.at(_spriteIndex);

	// 여기서 setTransform를 해주자. 그리기 전에 해야함. 
	m_pRenderTarget->SetTransform(_object->GetTransform()->GetWorldTransformMatrix() * _viewTM);

	if (_sprite != nullptr)
	{
		m_pRenderTarget->DrawBitmap(_spriteSheet->m_pBitmapAddress,
			D2D1::RectF(0 - _spriteSheet->m_ScrSize.m_x, 0 - _spriteSheet->m_ScrSize.m_y, 
				0 + _spriteSheet->m_ScrSize.m_x, 0 + _spriteSheet->m_ScrSize.m_y), // 화면에 위치하는 사각형의 크기? 좌표? 
			1.0f, // 불투명도 
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(_sprite->x, _sprite->y, _sprite->width, _sprite->height)); // sheet를 필요한 만큼 잘라낸 사각형 크기? 좌표  
	}

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}*/

HBSpriteSheet* ImageLoader::GetSpriteSheetInfo(int _sheetIndex)
{
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(_sheetIndex);

	return _spriteSheet;
}

void ImageLoader::PlayAnimation(GameObject* _object, int _sheetIndex, D2D1::Matrix3x2F _viewTM)
{
	// m_SpriteInfos에 들어있는 이미지를 가져옴.
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(_sheetIndex);
	HBSprite* _sprite = _spriteSheet->m_Sprites.at(m_CurrentIndex);

	// 현재 sheet에서 어디를 중점으로 그리고 있는지 그 위치를 가져오자. 
	int m_PosInSheetX = _sprite->width / 2.0f;
	int m_PosInSheetY = _sprite->height / 2.0f;

	// 애니메이션 시간에 현재 deltaTime를 받아온다. 
	m_FlowTime += HBTime::GetInstance()->GetDeltaTime();

	// m_FlowTime은 시작시간이 0초부터 시작하기 때문에 
	// m_DDelayTime 보다 작을 수 밖에 없음. 
	// m_flowTime이 m_DelayTime 보다 커지는 순간 m_CurrentIndex++ 해줌.
	if (m_DelayTime <= m_FlowTime)
	{
		// m_CurrentIndex++ 하여 m_FrameCount를 보다 커졌을때, 
		// 나머지 연산자를 통해 다시 0으로 되돌려줌. 
		m_CurrentIndex = (m_CurrentIndex + 1) % _spriteSheet->m_FrameCount;

		// 현재시간을 0으로 만듦
		m_FlowTime = 0.f;
	}

	// _spriteIndex를 변화된 m_CurrentIndex로 바꿔줌.
	m_CurrentIndex = m_CurrentIndex;

	/// 싱글턴의 악몽...
	// 바뀐 m_CurrentIndex를 인자로 넣어서 그려주자.
	// DrawSprite(_object, _sheetIndex, m_CurrentIndex, _viewTM);
}

void ImageLoader::Release()
{
	/// 사용한 객체들을 모두 해제.
	for (int i = 0; i < m_SpriteCount; i++)
	{
		delete	m_SpriteSheetInfos.at(i);
	}

	delete m_pShape;

	SafeRelease(&m_pRenderTarget);
	//SafeRelease(&m_pD2DBitmap);
	//SafeRelease(&m_pConvertedSrcBmp);
	//SafeRelease(&m_pWICFactory);
}
