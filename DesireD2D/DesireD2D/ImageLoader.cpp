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
	// DesireD2D���� ImageLoader->Release()�� ȣ�����ش�. 
	// ���� ���⼭ �ѹ� �� ���Ÿ� �ؾ� �ϳ�? 
	// Release();
	DestroyInstance();
}

/*
HRESULT ImageLoader::CreateWICFactory(ID2D1HwndRenderTarget* pRenderTarget)
{
	HRESULT hr = S_OK;
	if (SUCCEEDED(hr))
	{
		// COM �ʱ�ȭ
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
	// wcstringd�� ���ڿ� ��
	size_t _NewSize = strlen(orig) + 1;

	// ���ڿ��� �� ��ŭ _WCString�� ���۸� ����� ��. 
	wchar_t* _WCString = new wchar_t[_NewSize];

	// char* �� wchar_t*�� ��ȯ
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
	// char ���� �ּҸ� wchar_t ������ �ٲ�����. 
	wchar_t* _WCString = this->ConvertCStoWCS(filePath);

	// �̹����� �ҷ��´�. 
	int _result = LoadSpriteSheet(_WCString, frameCount);

	// ������ ���� ����
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

	// �ҷ� �� ��Ʈ�� ����
	if (SUCCEEDED(hr))
	{
		m_SpriteSheetCount++;

		return (m_SpriteSheetCount - 1); // �־��� m_SpriteSheetCount�� +1�� ���־��� ������ �־��� m_SpriteSheetCount�� -1�� ������� �־��� sheet�� ���� �� �� ����. 
	}

	return -1; // �ڵ��� ������ ���� �߻�
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
		OutputDebugString(L"�ڵ� �޾ƿ��� ����^��^\n");
	}
	else
	{
		OutputDebugString(L"�ڵ� �޾ƿ��� ����8��8\n");
	}
}*/

/*
HBSpriteSheet* ImageLoader::SpriteSheetInfo(int index, int width, int highte, int frameCount)
{
	// ��������Ʈ Ŭ���� ����. 
	HBSpriteSheet* _newSpriteInfo = new HBSpriteSheet(index, width, highte, 0, 0, frameCount);

	// ������ ��������Ʈ ������ m_SpriteInfos�� �־��ش�. 
	m_SpriteSheetInfos.push_back(_newSpriteInfo);
	m_SpriteCount++;

	return _newSpriteInfo;
}*/

/*
void ImageLoader::SpriteSheetInfo(int width, int highte, int frameCount)
{
	// ��������Ʈ Ŭ���� ����. 
	HBSpriteSheet* _newSpriteInfo = new HBSpriteSheet(width, highte, 0, 0, frameCount);

	// ������ ��������Ʈ ������ m_SpriteInfos�� �־��ش�. 
	m_SpriteSheetInfos.push_back(_newSpriteInfo);
	m_SpriteCount++;
}*/

/*
void ImageLoader::SpriteSheetInfo(ID2D1Bitmap* Bitmap, int width, int height, int frameCount)
{
	// ��������Ʈ Ŭ���� ����. 
	HBSpriteSheet* _newSpriteInfo = new HBSpriteSheet(width, height, 0, 0, frameCount);

	_newSpriteInfo->m_pBitmapAddress = Bitmap;

	// �ִϸ��̼��� ������ frameCount��ŭ �ڸ��� ��������Ʈ ���Ϳ� �־�����. 
	if (frameCount != 0)
	{
		// �����̹����� ������ �� ��ŭ �ڸ���.
		int _offset = width / frameCount;
		int _y = 0;

		// ��������Ʈ sheet�� ������ ������ �� �ѹ� ����� �ָ� ��. 
		// ������������ sprite�� ũ��
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
		// ������������ sprite�� ũ��
		_newSpriteInfo->m_ScrSize.m_x = width / 2.0f;
		_newSpriteInfo->m_ScrSize.m_y = height / 2.0f;
		HBSprite* _newSprite = new HBSprite(0, 0, width, height);
		_newSpriteInfo->m_Sprites.push_back(_newSprite);
		m_SpriteCount++;
	}

	// ������ ��������Ʈ ������ m_SpriteInfos�� �־��ش�. 
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
	// m_SpriteInfos�� ����ִ� �̹����� ������.
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(_sheetIndex);

	HBSprite* _sprite = _spriteSheet->m_Sprites.at(_spriteIndex);

	// ���⼭ setTransform�� ������. �׸��� ���� �ؾ���. 
	m_pRenderTarget->SetTransform(_viewTM);

	if (_sprite != nullptr)
	{
		m_pRenderTarget->DrawBitmap(_spriteSheet->m_pBitmapAddress,
			D2D1::RectF((float)(_posX - _spriteSheet->m_ScrSize.m_x),
				(float)(_posY - _spriteSheet->m_ScrSize.m_y),
				(float)(_posX + _spriteSheet->m_ScrSize.m_x), 
				(float)(_posY + _spriteSheet->m_ScrSize.m_y)), // ȭ�鿡 ��ġ�ϴ� �簢���� ũ��? ��ǥ? 
			1.0f, // ������ 
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(_sprite->x, _sprite->y, _sprite->width, _sprite->height)); // sheet�� �ʿ��� ��ŭ �߶� �簢�� ũ��? ��ǥ  
	}
}*/

/*
void ImageLoader::DrawSprite(GameObject* _object, int _sheetIndex, int _spriteIndex, D2D1::Matrix3x2F _viewTM)
{
	// m_SpriteInfos�� ����ִ� �̹����� ������.
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(_sheetIndex);

	HBSprite* _sprite = _spriteSheet->m_Sprites.at(_spriteIndex);

	// ���⼭ setTransform�� ������. �׸��� ���� �ؾ���. 
	m_pRenderTarget->SetTransform(_object->GetTransform()->GetWorldTransformMatrix() * _viewTM);

	if (_sprite != nullptr)
	{
		m_pRenderTarget->DrawBitmap(_spriteSheet->m_pBitmapAddress,
			D2D1::RectF(0 - _spriteSheet->m_ScrSize.m_x, 0 - _spriteSheet->m_ScrSize.m_y, 
				0 + _spriteSheet->m_ScrSize.m_x, 0 + _spriteSheet->m_ScrSize.m_y), // ȭ�鿡 ��ġ�ϴ� �簢���� ũ��? ��ǥ? 
			1.0f, // ������ 
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(_sprite->x, _sprite->y, _sprite->width, _sprite->height)); // sheet�� �ʿ��� ��ŭ �߶� �簢�� ũ��? ��ǥ  
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
	// m_SpriteInfos�� ����ִ� �̹����� ������.
	HBSpriteSheet* _spriteSheet = m_SpriteSheetInfos.at(_sheetIndex);
	HBSprite* _sprite = _spriteSheet->m_Sprites.at(m_CurrentIndex);

	// ���� sheet���� ��� �������� �׸��� �ִ��� �� ��ġ�� ��������. 
	int m_PosInSheetX = _sprite->width / 2.0f;
	int m_PosInSheetY = _sprite->height / 2.0f;

	// �ִϸ��̼� �ð��� ���� deltaTime�� �޾ƿ´�. 
	m_FlowTime += HBTime::GetInstance()->GetDeltaTime();

	// m_FlowTime�� ���۽ð��� 0�ʺ��� �����ϱ� ������ 
	// m_DDelayTime ���� ���� �� �ۿ� ����. 
	// m_flowTime�� m_DelayTime ���� Ŀ���� ���� m_CurrentIndex++ ����.
	if (m_DelayTime <= m_FlowTime)
	{
		// m_CurrentIndex++ �Ͽ� m_FrameCount�� ���� Ŀ������, 
		// ������ �����ڸ� ���� �ٽ� 0���� �ǵ�����. 
		m_CurrentIndex = (m_CurrentIndex + 1) % _spriteSheet->m_FrameCount;

		// ����ð��� 0���� ����
		m_FlowTime = 0.f;
	}

	// _spriteIndex�� ��ȭ�� m_CurrentIndex�� �ٲ���.
	m_CurrentIndex = m_CurrentIndex;

	/// �̱����� �Ǹ�...
	// �ٲ� m_CurrentIndex�� ���ڷ� �־ �׷�����.
	// DrawSprite(_object, _sheetIndex, m_CurrentIndex, _viewTM);
}

void ImageLoader::Release()
{
	/// ����� ��ü���� ��� ����.
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
