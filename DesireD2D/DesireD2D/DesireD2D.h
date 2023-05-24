#pragma once
#include "pch.h"
#include <vector>
#include <map>

class CircleCollision;
class BoxCollision;
class Transform;
class ImageLoader;
class GameObject;

class DesireD2D
{
public:
	DesireD2D();
	~DesireD2D();

private:
	/// D2D 초기화에 필요한 변수들
	HWND m_hwnd;
	HRESULT m_hr;

	ID2D1Factory* m_pFactory;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

	/// bitmap를 사용하기 위한 변수
	IWICImagingFactory* m_pWICFactory; //디코더, 인코더 및 픽셀 형식 변환기와 같은 WIC(Windows Imaging Component)용 구성 요소를 만드는 데 사용
	IWICFormatConverter* m_pConvertedSrcBmp;
	ID2D1Bitmap* m_pD2DBitmap;

	/// effect를 위한 변서
	ID2D1DeviceContext* m_pDeviceContext;
	ID2D1Effect* m_pGaussianBlur;

	/// bitmap 이미지를 불로오고 그려줄 변수 
	// ImageLoader* m_pImageLoader;

	/// D2D 엔진을 사용하기 위한 변수 
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pBrush;
	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1SolidColorBrush* m_pGreenBrush;
	ID2D1SolidColorBrush* m_pYellowBrush;
	ID2D1SolidColorBrush* m_pFontBrush;

	/// 충돌박스 변수
	CircleCollision* m_pCCollision;
	BoxCollision* m_pAABB;

	/// 오브젝트 변환하기 위한 변수
	Transform* m_pTransform;

	/// 엔진내의 카메라 뷰트랜스폼매트릭스 (Camera View Transform Matrix = 카메라 자체 Transform의 역변환)
	D2D1::Matrix3x2F m_ViewTM;

private:

	/// 그래픽 엔진 초기화 함수
	HRESULT CreateFactory();
	HRESULT CreateGraphicsResources(); // rendertarget, brush 생성
	HRESULT CreateTextResources();
	HRESULT CreateWICFactory(); // WICFatory 초기화

	/// 포인터 변수들을 해제하는 함수
	void DiscardGraphicsResources();

	/// bitmap file를 불러오는 함수들
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

	
	/// 도형 만들어주는 함수
	void CalculateLayout();

	/// 충돌 체크하는 함수
	void AxisAlinedBoundingBox(D2D1_RECT_F rect1, D2D1_RECT_F rect2);

public:
	const wchar_t* m_wszText;
	UINT32 m_cTextLength;

	/// 스프라이트의 정보를 저장한 벡터.
	std::vector<HBSpriteSheet*> m_SpriteSheetInfos;

	/// sprite 관련 변수
	int m_SpriteCount;
	int m_SpriteSheetCount;

	/// 애니메이션을 돌리기 위해 필요한 변수
	// 스프라이트가 출력되는 시간
	float m_FlowTime;

	// 스프라이트를 얼마동안 출력할 것인지에 대한 시간
	float m_DelayTime;

	// 애니메이션이 되여야 하는 수
	int m_FrameNum;

	D2D1_ELLIPSE m_ellipse1;
	D2D1_ELLIPSE m_ellipse2;
	D2D1_RECT_F m_rectangle1;
	D2D1_RECT_F m_rectangle2;

	float m_rectPosX;
	float m_rectPosY;

	float m_Size;

	/// getter, setter 변수들
	Transform* GetTransform() const { return m_pTransform; }
	D2D1::Matrix3x2F GetViewTM() const { return m_ViewTM; }

public:
	// factory 초기화 함수
	void Initialize(HWND hWnd);

	// 엔진 내부 정보를 업데이트
	void Update(D2D1::Matrix3x2F viewTM/*, D2D1::Matrix3x2F projectionTM*/);

	// 그리기에 필요한 함수 
	void BeginRender();
	void OnRender();		// 그려주는 함수 
	void EndRender();

	void OnDeviceLost();	// 특정 이유(창 크기 변경, Alt+Tab)로 렌더타겟이 소실되었을 때 호출해 줌


	void SetTransformLocal();	// 트랜스폼을 로컬기준으로
	void SetTransformView();	// 카메라만 적용 시킨 상태로


	// 시작좌표에서 끝좌표까지 선을 그린다.  
	void DrawLine(float startX, float startY, float endX,  float endY);
	
	// posX, posY 값을 중점으로 radius만큼 원을 그린다. 
	void DrawEllipse(float posX, float posY, float radius);

	// posX, posY 값을 중점으로 radius만큼 정사각형을 그린다. 
	void DrawRectangle(float posX, float posY, float radius);

	// posX, posY 값을 중점으로 width, height만큼 직사각형을 그린다. 
	void DrawRectangle(float posX, float posY, float width, float height);
	void DrawRectangle(D2D1_RECT_F rect, D2D1::Matrix3x2F worldTM = D2D1::Matrix3x2F::Identity(), bool localSpace = false);
	void DrawRectangleR(D2D1_RECT_F rect, D2D1::Matrix3x2F worldTM = D2D1::Matrix3x2F::Identity(), bool localSpace = false);
	void DrawRectangleY(D2D1_RECT_F rect, D2D1::Matrix3x2F worldTM = D2D1::Matrix3x2F::Identity(), bool localSpace = false);


	/// 디버그 데이터를 위한 함수들

	// 자신의 스프라이트 이미지만큼 충돌박스를 그려주는 함수
	void DrawCollisionRect_Dev(float posX, float posY, int Sheetindex, int Spriteindex, bool ScreenSpace = false);

	// 원하는 좌표에 텍스트를 띄운다. 
	void DrawText(float posX, float posY, const char* pch, ...);

	// 스프라이트를 그려주는 함수 
	void DrawBitmap();
	void DrawSprite(int _sheetIndex, int _spriteIndex, int _posX, int _posY);
	void DrawSprite(Transform* pTransform, int _sheetIndex, int _spriteIndex);

	// 스프라이트를 리턴하는 함수
	HBSprite* GetSprite(int sheetIndex, int spriteIndex);
	D2D1_RECT_F GetSpriteRect(int sheetIndex, int spriteIndex);


	/// file의 주소와 원본사이즈, 프레임 수를 들고와서 대입한다. 
	int LoadSpriteSheet(const char* filePath, int frameCount); // 스프라이트 시트 로드
	int LoadSpriteSheet(const wchar_t* filePath, int frameCount);

	// sprite 정보를 HBSprite* 에 넣어주는 함수
	HBSpriteSheet* SpriteSheetInfo(int index, int width, int height, int frameCount);
	void SpriteSheetInfo(int width, int height, int frameCount);
	void SpriteSheetInfo(ID2D1Bitmap* Bitmap, int width, int height, int frameCount);

	// sheet를 원하는 크기 만큼 자르는 함수
	HBSprite* SplitSpriteSheet(int x, int y, int width, int height);

	// m_SpriteSheetInfos에 있는 HBSpriteSheet를 가져오는 함수. 
	HBSpriteSheet* GetSpriteSheetInfo(int _sheetIndex);

	void PlayAnimation(GameObject* _object, int _sheetIndex, int* _spriteIndex);

	// Move 함수들
	void EllipseMove(D2D1_ELLIPSE ellipse, float posX, float posY);

	void RectangleMove(D2D1_RECT_F rect, float posX, float posY);

	// effect 함수 
	void SetGaussianBlurEffect(ID2D1Bitmap** pBitmap);



	/// 물리엔진/충돌감지
	bool Collision_AABB(D2D1_RECT_F rt1, D2D1_RECT_F rt2);


};


