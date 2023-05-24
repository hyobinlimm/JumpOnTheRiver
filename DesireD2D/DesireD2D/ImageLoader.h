#pragma once
#include <vector>
#include <map>
#include "TamplateSingleton.h"
#include "HBVector2.h"

class HBSpriteSheet;
class HBSprite;
class GameObject;
class Shape;

/// <summary>
/// 이미지 경로를 받아옴
/// 받아온 이미지를 화면에 출력
/// 
/// 22.02.09. hyobin
/// </summary>

class ImageLoader : public TemplateSingleton<ImageLoader>
{
public:
	ImageLoader();
	~ImageLoader();

private:
	/// bitmap를 사용하기 위한 변수
	//IWICImagingFactory* m_pWICFactory; //디코더, 인코더 및 픽셀 형식 변환기와 같은 WIC(Windows Imaging Component)용 구성 요소를 만드는 데 사용
	//IWICFormatConverter* m_pConvertedSrcBmp;
	//ID2D1Bitmap* m_pD2DBitmap;

	/// bitmap를 그리는 곳을 알려줄 변수 
	ID2D1HwndRenderTarget* m_pRenderTarget;

	/// 도형을 만들어주는 변수
	Shape* m_pShape;

	// 스프라이트가 출력되는 시간
	float m_FlowTime;

	// 스프라이트를 얼마동안 출력할 것인지에 대한 시간
	float m_DelayTime;

	// 그려지는 스프라이트의 인덱스 
	int m_CurrentIndex;

	// 애니메이션이 되여야 하는 수
	int m_FrameNum;

public:
	/// sprite 관련 변수
	int m_SpriteCount;
	int m_SpriteSheetCount;

	/// 스프라이트의 정보를 저장한 벡터.
	std::vector<HBSpriteSheet*> m_SpriteSheetInfos;	

private:
	// bitmap를 불러오는 함수들 
	HRESULT LoadResourceBitmap(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	// Create a bitmap by loading it from a file.
	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	// cstring 문자열을 wcstirng으로 바꾸는 함수 
	wchar_t* ConvertCStoWCS(const char* orig);

public:

	/// WICFatory 초기화
	//HRESULT CreateWICFactory(ID2D1HwndRenderTarget* pRenderTarget);
	void initialize(ID2D1HwndRenderTarget* pRenderTarget);

	// sprite 관련 함수들
	//int LoadSpriteSheet(const char* filePath, int frameCount); // 스프라이트 시트 로드
	//int LoadSpriteSheet(const wchar_t* filePath, int frameCount);

	// 이미지 로드하는 함수
	void LoadImageResource(ID2D1HwndRenderTarget* m_pRenderTarget);

	// sprite 정보를 HBSprite* 에 넣어주는 함수
	// HBSpriteSheet* SpriteSheetInfo(int index, int width, int height, int frameCount);
	// void SpriteSheetInfo(int width, int height, int frameCount);
	// void SpriteSheetInfo(ID2D1Bitmap* Bitmap, int width, int height, int frameCount);

	// sheet를 원하는 크기 만큼 자르는 함수
	// HBSprite* SplitSpriteSheet(int x, int y, int width, int height);

	//void DrawBitmap();
	//void DrawSprite(int _sheetIndex, int _spriteIndex, int _posX, int _posY, D2D1::Matrix3x2F _viewTM);
	//void DrawSprite(GameObject* _object, int _sheetIndex, int _spriteIndex, D2D1::Matrix3x2F _viewTM);

	// m_SpriteSheetInfos에 있는 HBSpriteSheet를 가져오는 함수. 
	HBSpriteSheet* GetSpriteSheetInfo(int _sheetIndex);

	void PlayAnimation(GameObject* _object, int _sheetIndex, D2D1::Matrix3x2F _viewTM);

	// 이미지를 해지하는 함수
	void Release();
};

