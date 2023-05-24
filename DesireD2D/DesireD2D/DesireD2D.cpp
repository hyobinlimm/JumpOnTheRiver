// DesireD2D.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "DesireD2D.h"
#include "ImageLoader.h"
#include "HBSprite.h"
#include <math.h>
#include "CircleCollision.h"
#include "BoxCollision.h"
#include "Transform.h"
#include "HBTime.h"
#include <CString>
#include "Shape.h"
#include "GameObject.h"

DesireD2D::DesireD2D()
	:m_hwnd(NULL), m_hr(S_OK), m_pFactory(nullptr), m_pDWriteFactory(nullptr), m_pTextFormat(nullptr),
	m_pWICFactory(nullptr), m_pConvertedSrcBmp(nullptr), m_pD2DBitmap(nullptr),
	m_pDeviceContext(nullptr), m_pGaussianBlur(nullptr),
	m_pRenderTarget(nullptr),
	m_pBrush(nullptr), m_pRedBrush(nullptr), m_pGreenBrush(nullptr), m_pYellowBrush(nullptr),
	m_pFontBrush(nullptr),
	m_pCCollision(nullptr), m_pAABB(nullptr),
	m_pTransform(nullptr),
	m_wszText(nullptr), m_cTextLength(NULL),
	m_SpriteCount(0), m_SpriteSheetCount(0),
	m_FlowTime(0), m_DelayTime(0.4f), m_FrameNum(0),
	m_ellipse1({ 0, }), m_ellipse2({ 0, }), m_rectangle1({ 0, }), m_rectangle2({ 0, }),
	m_rectPosX(0), m_rectPosY(0), m_Size(50)
{

}

DesireD2D::~DesireD2D()
{
	DiscardGraphicsResources();
	SafeRelease(&m_pFactory);
}


HRESULT DesireD2D::CreateFactory()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory
	if (SUCCEEDED(hr))
	{
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	}

	return hr;
}

HRESULT DesireD2D::CreateGraphicsResources()
{
	HRESULT hr = S_OK;

	if (m_pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = m_pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget);

		if (SUCCEEDED(hr))
		{
			const D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Navy);
			hr = m_pRenderTarget->CreateSolidColorBrush(color, &m_pBrush);
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &m_pRedBrush);
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &m_pGreenBrush);
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &m_pYellowBrush);

			if (SUCCEEDED(hr))
			{
				CalculateLayout();
			}
		}

		// Create a black brush.
		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pFontBrush);
		}
	}

	m_pRenderTarget->QueryInterface(&m_pDeviceContext);

	return hr;
}

HRESULT DesireD2D::CreateTextResources()
{
	HRESULT hr = S_OK;

	m_wszText = L"아이고 이런";
	m_cTextLength = (UINT32)wcslen(m_wszText);

	// Create a DirectWrite factory.
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}

	// Create a DirectWrite text format object.
	if (SUCCEEDED(hr))
	{
		hr = m_pDWriteFactory->CreateTextFormat(
			m_wszText, NULL, DWRITE_FONT_WEIGHT_BOLD,
			DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
			15, L"", &m_pTextFormat);
	}

	// Center the text horizontally and vertically.
	if (SUCCEEDED(hr))
	{
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	return hr;
}

HRESULT DesireD2D::CreateWICFactory()
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

	return hr;
}

void DesireD2D::DiscardGraphicsResources()
{
	/// 사용한 객체들을 모두 해제.
	for (int i = 0; i < m_SpriteCount; i++)
	{
		delete	m_SpriteSheetInfos[i];
	}

	SafeRelease(&m_pGaussianBlur);
	SafeRelease(&m_pDeviceContext);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pBrush);
	SafeRelease(&m_pFontBrush);
	SafeRelease(&m_pYellowBrush);
	SafeRelease(&m_pGreenBrush);
	SafeRelease(&m_pRedBrush);

	delete m_pCCollision;
	delete m_pAABB;
	delete m_pTransform;
	delete m_wszText;

	m_cTextLength = NULL;
	m_ellipse1 = { NULL, };
	m_ellipse2 = { NULL, };
	m_rectangle1 = { NULL, };
	m_rectangle2 = { NULL, };

	m_rectPosX = NULL;
	m_rectPosY = NULL;

	m_Size = NULL;
}

HRESULT DesireD2D::LoadResourceBitmap(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR resourceName, PCWSTR resourceType, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void* pImageFile = NULL;
	DWORD imageFileSize = 0;

	// Locate the resource.
	imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);
	HRESULT hr = imageResHandle ? S_OK : E_FAIL;

	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;

	}

	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = pIWICFactory->CreateStream(&pStream);
	}
	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = pIWICFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut);
	}

	// 다른 Direct2D 개체와 함께 사용할 수 있는 ID2D1Bitmap 개체를 만듭
	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

HRESULT DesireD2D::LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	// 이미지에서 프레임을 검색하고  IWICBitmapFrameDecode 개체에 프레임을 저장
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);

	}

	// IWICFormatConverter 개체의 Initialize 메서드를 호출하여 변환을 수행
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	// CreateBitmapFromWicBitmap 메서드를 호출하여 렌더링 대상에서 그리고 다른 Direct2D 개체와 함께 사용할 수 있는 ID2D1Bitmap 개체를 만듬.
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

wchar_t* DesireD2D::ConvertCStoWCS(const char* orig)
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

int DesireD2D::LoadSpriteSheet(const char* filePath, int frameCount)
{
	// char 형의 주소를 wchar_t 형으로 바꿔주자. 
	wchar_t* _WCString = this->ConvertCStoWCS(filePath);

	// 이미지를 불러온다. 
	int _result = LoadSpriteSheet(_WCString, frameCount);

	// 포인터 변수 해제
	delete[] _WCString;

	return _result;
}

int DesireD2D::LoadSpriteSheet(const wchar_t* filePath, int frameCount)
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
}

void DesireD2D::CalculateLayout()
{
	if (m_pRenderTarget != NULL)
	{
		D2D1_SIZE_F size = m_pRenderTarget->GetSize();
		const float x = 300;
		const float y = 200;
		const float radius = 50;

		m_rectPosX = 800.f;
		m_rectPosY = 300.f;

		m_ellipse1 = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
		m_ellipse2 = D2D1::Ellipse(D2D1::Point2F(x + 100, y + 100), radius, radius);
		//m_rectangle1 = D2D1::RectF(m_rectPosX - 50.0f, m_rectPosY - 50.0f, m_rectPosX + 60.0f, m_rectPosY + 60.0f);
		m_rectangle2 = D2D1::RectF(m_rectPosX + 150.0f, m_rectPosY + 150.0f, m_rectPosX + 250.0f, m_rectPosY + 250.0f);

		// TODO
	}
}

void DesireD2D::AxisAlinedBoundingBox(D2D1_RECT_F rect1, D2D1_RECT_F rect2)
{
	if ((rect1.right > rect2.left && rect1.left < rect2.right) &&
		(rect1.bottom > rect2.top && rect1.top < rect2.bottom))
	{
		m_pRenderTarget->DrawRectangle(rect1, m_pRedBrush);
		m_pRenderTarget->DrawRectangle(rect2, m_pRedBrush);
	}
}

void DesireD2D::Initialize(HWND hWnd)
{
	m_hwnd = hWnd;

	m_hr = CreateFactory();
	m_hr = CreateGraphicsResources();
	m_hr = CreateTextResources();
	m_hr = CreateWICFactory();

	m_pCCollision = new CircleCollision();
	m_pAABB = new BoxCollision();

	m_pTransform = new Transform();

	// 이미지 로드 해봄 (test)
	//m_pImageLoader->LoadSpriteSheet(L"../DesireD2D/DesireD2D/Data/sheet.PNG");
	//m_pImageLoader->SpriteSheetInfo(256, 256, 4);
}

void DesireD2D::Update(D2D1::Matrix3x2F viewTM/*, D2D1::Matrix3x2F projectionTM*/)
{
	m_ViewTM = viewTM;
}

void DesireD2D::BeginRender()
{
	if (SUCCEEDED(m_hr))
	{
		m_pRenderTarget->BeginDraw();	// 이제 그릴겨
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Yellow));	// 화면 색 초기화 
	}
}

void DesireD2D::OnRender()
{
	float _rectWidth = m_rectangle1.right - m_rectangle1.left;
	float _rectheight = m_rectangle1.bottom - m_rectangle1.top;

	if (SUCCEEDED(m_hr))
	{
		/// 이펙트를 적용시키고 싶었음. 
		ID2D1Bitmap* _pD2DBitmap = m_SpriteSheetInfos.at(1)->m_pBitmapAddress;
		SetGaussianBlurEffect(&_pD2DBitmap);
		m_pDeviceContext->DrawImage(m_pGaussianBlur);


		// 사각형의 위치 자체
		m_rectangle1 = D2D1::RectF(m_rectPosX - m_Size, m_rectPosY - m_Size, m_rectPosX + m_Size, m_rectPosY + m_Size);

		D2D1_SIZE_F RenderTargetSize = m_pRenderTarget->GetSize(); // 그릴 화면 사이즈 가져오기 

		m_pRenderTarget->DrawEllipse(m_ellipse1, m_pGreenBrush);
		m_pRenderTarget->DrawEllipse(m_ellipse2, m_pBrush);

		m_pRenderTarget->FillRectangle(m_rectangle1, m_pBrush);
		m_pRenderTarget->FillRectangle(m_rectangle2, m_pGreenBrush);

		m_pCCollision->CheckCollision(m_ellipse1, m_ellipse2);
		if (m_pCCollision->m_isCollided == true)
		{
			m_pRenderTarget->DrawEllipse(m_ellipse1, m_pRedBrush);
			m_pRenderTarget->DrawEllipse(m_ellipse2, m_pRedBrush);
		}

		m_pAABB->AxisAlinedBoundingBox(m_rectangle1, m_rectangle2);
		if (m_pAABB->m_isCollided == true)
		{
			m_pRenderTarget->DrawRectangle(m_rectangle1, m_pRedBrush);
			m_pRenderTarget->DrawRectangle(m_rectangle2, m_pRedBrush);
		}

		m_pRenderTarget->DrawText(m_wszText, m_cTextLength, m_pTextFormat,
			D2D1::RectF(0, 0, RenderTargetSize.width, RenderTargetSize.height), m_pFontBrush);



		/// 2D는 m_pRenderTarget이라는 도화지를 돌려서 그려주는 것이기 때문에 
		/// m_pRenderTarget->SetTransform()이라는 함수를 통해 도화지 자체를 회전시켜야 함.
		//m_pRenderTarget->SetTransform()

		//m_pImageLoader->DrawSprite(0, 0);
	}
}

void DesireD2D::EndRender()
{
	m_hr = m_pRenderTarget->EndDraw();
}

void DesireD2D::OnDeviceLost()
{
	if (m_pRenderTarget != NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		m_pRenderTarget->Resize(size);

		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

void DesireD2D::SetTransformLocal()
{
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void DesireD2D::SetTransformView()
{
	m_pRenderTarget->SetTransform(m_ViewTM);
}

void DesireD2D::DrawLine(float startX, float startY, float endX, float endY)
{
	m_pRenderTarget->DrawLine({ startX, startY }, { endX, endY }, m_pGreenBrush);
}

void DesireD2D::DrawEllipse(float posX, float posY, float radius)
{
	D2D1_ELLIPSE _ellipse = D2D1::Ellipse(D2D1::Point2F(posX, posY), radius, radius);

	m_pRenderTarget->DrawEllipse(m_ellipse1, m_pGreenBrush);
}

void DesireD2D::DrawRectangle(float posX, float posY, float radius)
{
	D2D1_RECT_F _rect = D2D1::RectF(posX - radius, posY - radius, posX + radius, posY + radius);

	m_pRenderTarget->DrawRectangle(_rect, m_pGreenBrush);
}

void DesireD2D::DrawRectangle(float posX, float posY, float width, float height)
{
	float _radiusX = width / 2;
	float _radiusY = height / 2;

	D2D1_RECT_F _rect = D2D1::RectF(posX - _radiusX, posY - _radiusY, posX + _radiusX, posY + _radiusY);

	m_pRenderTarget->DrawRectangle(_rect, m_pGreenBrush);
}

void DesireD2D::DrawRectangle(D2D1_RECT_F rect, D2D1::Matrix3x2F worldTM /*= D2D1::Matrix3x2F::Identity()*/, bool localSpace /*= false*/)
{
	if (localSpace == false) m_pRenderTarget->SetTransform(worldTM * m_ViewTM);

	m_pRenderTarget->DrawRectangle(rect, m_pGreenBrush);
}

void DesireD2D::DrawRectangleR(D2D1_RECT_F rect, D2D1::Matrix3x2F worldTM /*= D2D1::Matrix3x2F::Identity()*/, bool localSpace /*= false*/)
{
	if (localSpace == false) m_pRenderTarget->SetTransform(worldTM * m_ViewTM);

	m_pRenderTarget->DrawRectangle(rect, m_pRedBrush);
}

void DesireD2D::DrawRectangleY(D2D1_RECT_F rect, D2D1::Matrix3x2F worldTM /*= D2D1::Matrix3x2F::Identity()*/, bool localSpace /*= false*/)
{
	if (localSpace == false) m_pRenderTarget->SetTransform(worldTM * m_ViewTM);

	m_pRenderTarget->DrawRectangle(rect, m_pYellowBrush);
}

/// <summary>
/// 충돌 박스를 그리는 함수
/// </summary>
/// <param name="ScreenSpace">true면 카메라를 따르지 않고 화면에 그냥 그림. false면 카메라를 따라감</param>
void DesireD2D::DrawCollisionRect_Dev(float posX, float posY, int Sheetindex, int Spriteindex, bool ScreenSpace /*= false*/)
{
	// 화면 좌표계가 아니라 월드 좌표계라면, 카메라 적용을 해 준다.
	if (ScreenSpace == false)
	{
		m_pRenderTarget->SetTransform(m_ViewTM);
	}

	float _radiusX = m_SpriteSheetInfos.at(Sheetindex)->m_Sprites.at(Spriteindex)->width / 2;
	float _radiusY = m_SpriteSheetInfos.at(Sheetindex)->m_Sprites.at(Spriteindex)->height / 2;

	D2D1_RECT_F _rect = D2D1::RectF(posX - _radiusX, posY - _radiusY, posX + _radiusX, posY + _radiusY);

	HRESULT hr = S_OK;

	if (SUCCEEDED(hr))
	{
		 m_pRenderTarget->DrawRectangle(_rect, m_pGreenBrush);
	}
}

void DesireD2D::DrawText(float posX, float posY, const char* pch, ...)
{
	char* _pStr;
	int _TextLength;

	va_list ap; // 현재 읽고 있는 번지를 기억
	va_start(ap, pch); // ap포인터 변수가 첫번째 가변인수를 가리키도록 초기화 

	_TextLength = _vscprintf(pch, ap) + 1; // 문자열 + 가변인자까지의 길이를 구한다. 

	// 2. wchar_t 메모리 할당
	_pStr = new char[_TextLength];

	vsprintf_s(_pStr, _TextLength, pch, ap);
	va_end(ap);

	// 1. 멀티바이트 크기 계산 길이 변환
	int nLen = MultiByteToWideChar(CP_ACP, 0, _pStr, -1, NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 형 변환
	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
	::MultiByteToWideChar(CP_ACP, 0, _pStr, strlen(_pStr), unicodestr, nLen);

	HRESULT hr = S_OK;

	if (SUCCEEDED(hr))
	{
		// 오브젝트가 들고 있는 자신의 크기를 받아와서 콜리전을 그려준다. 
		m_pRenderTarget->DrawTextW(unicodestr, wcslen(unicodestr), m_pTextFormat,
			D2D1::RectF(posX, posY, posX + 500, posY + 30), m_pFontBrush);
	}

	::SysFreeString(unicodestr);

	delete[] _pStr;

}

void DesireD2D::DrawBitmap()
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

void DesireD2D::DrawSprite(int _sheetIndex, int _spriteIndex, int _posX, int _posY)
{
	// m_SpriteInfos에 들어있는 이미지를 가져옴.
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(_sheetIndex);

	HBSprite* _sprite = _spriteSheet->m_Sprites.at(_spriteIndex);

	// 여기서 setTransform를 해주자. 그리기 전에 해야함. 
	m_pRenderTarget->SetTransform(m_ViewTM);

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
}

void DesireD2D::DrawSprite(Transform* pTransform, int _sheetIndex, int _spriteIndex)
{
	// m_SpriteInfos에 들어있는 이미지를 가져옴.
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(_sheetIndex);

	HBSprite* _sprite = _spriteSheet->m_Sprites.at(_spriteIndex);

	// 여기서 setTransform를 해주자. 그리기 전에 해야함. 
	m_pRenderTarget->SetTransform(pTransform->GetWorldTransformMatrix() * m_ViewTM);

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
}

// m_SpriteInfos에 들어있는 이미지를 가져옴
HBSprite* DesireD2D::GetSprite(int sheetIndex, int spriteIndex)
{
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(sheetIndex);

	if (_spriteSheet)
	{
		HBSprite* _sprite = _spriteSheet->m_Sprites.at(spriteIndex);
		return _sprite;
	}

	return nullptr;
}


D2D1_RECT_F DesireD2D::GetSpriteRect(int sheetIndex, int spriteIndex)
{
	float _radiusX = m_SpriteSheetInfos.at(sheetIndex)->m_Sprites.at(spriteIndex)->width / 2;
	float _radiusY = m_SpriteSheetInfos.at(sheetIndex)->m_Sprites.at(spriteIndex)->height / 2;

	return D2D1::RectF(-_radiusX, -_radiusY, _radiusX, _radiusY);
}

HBSpriteSheet* DesireD2D::SpriteSheetInfo(int index, int width, int height, int frameCount)
{
	// 스프라이트 클래스 생성. 
	HBSpriteSheet* _newSpriteInfo = new HBSpriteSheet(index, width, height, 0, 0, frameCount);

	// 생성된 스프라이트 정보를 m_SpriteInfos에 넣어준다. 
	m_SpriteSheetInfos.push_back(_newSpriteInfo);
	m_SpriteCount++;

	return _newSpriteInfo;
}

void DesireD2D::SpriteSheetInfo(int width, int height, int frameCount)
{
	// 스프라이트 클래스 생성. 
	HBSpriteSheet* _newSpriteInfo = new HBSpriteSheet(width, height, 0, 0, frameCount);

	// 생성된 스프라이트 정보를 m_SpriteInfos에 넣어준다. 
	m_SpriteSheetInfos.push_back(_newSpriteInfo);
	m_SpriteCount++;
}

void DesireD2D::SpriteSheetInfo(ID2D1Bitmap* Bitmap, int width, int height, int frameCount)
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
}

HBSprite* DesireD2D::SplitSpriteSheet(int x, int y, int width, int height)
{
	HBSprite* _newSprite = new HBSprite(x, y, width, height);

	return _newSprite;
}

HBSpriteSheet* DesireD2D::GetSpriteSheetInfo(int _sheetIndex)
{
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(_sheetIndex);

	return _spriteSheet;
}

void DesireD2D::PlayAnimation(GameObject* _object, int _sheetIndex, int* _spriteIndex)
{
	// m_SpriteInfos에 들어있는 이미지를 가져옴.
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(_sheetIndex);
	HBSprite* _sprite = _spriteSheet->m_Sprites.at(*_spriteIndex);

	// 현재 sheet에서 어디를 중점으로 그리고 있는지 그 위치를 가져오자. 
	int m_PosInSheetX = _sprite->width / 2;
	int m_PosInSheetY = _sprite->height / 2;

	// 애니메이션 시간에 현재 deltaTime를 받아온다. 
	m_FlowTime += HBTime::GetInstance()->GetDeltaTime();

	// m_FlowTime은 시작시간이 0초부터 시작하기 때문에 
	// m_DDelayTime 보다 작을 수 밖에 없음. 
	// m_flowTime이 m_DelayTime 보다 커지는 순간 m_CurrentIndex++ 해줌.
	if (m_DelayTime <= m_FlowTime)
	{
		// 프레임 카운트에 따라서 다르게 처리합니다.
		(*_spriteIndex) = ((*_spriteIndex) + 1) % _spriteSheet->m_FrameCount;

		// 현재시간을 0으로 만듦
		m_FlowTime = 0.f;
	}

	/// 싱글턴의 악몽...
	// 바뀐 m_CurrentIndex를 인자로 넣어서 그려주자.
	DrawSprite(_object->GetTransform(), _sheetIndex, (*_spriteIndex));
}

void DesireD2D::EllipseMove(D2D1_ELLIPSE ellipse, float posX, float posY)
{
	ellipse.point.x = posX;
	ellipse.point.y = posY;
}

void DesireD2D::RectangleMove(D2D1_RECT_F rect, float posX, float posY)
{
	m_rectPosX = posX;
	m_rectPosY = posY;
}

void DesireD2D::SetGaussianBlurEffect(ID2D1Bitmap** pBitmap)
{
	m_pDeviceContext->CreateEffect(CLSID_D2D1GaussianBlur, &m_pGaussianBlur);

	m_pGaussianBlur->SetInput(0, *pBitmap);
	m_pGaussianBlur->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 3.0f);
}

bool DesireD2D::Collision_AABB(D2D1_RECT_F rt1, D2D1_RECT_F rt2)
{
	return ((rt1.right > rt2.left && rt1.left < rt2.right) &&
		(rt1.bottom > rt2.top && rt1.top < rt2.bottom));
}

