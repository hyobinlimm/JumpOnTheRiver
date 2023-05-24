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
	/// D2D �ʱ�ȭ�� �ʿ��� ������
	HWND m_hwnd;
	HRESULT m_hr;

	ID2D1Factory* m_pFactory;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

	/// bitmap�� ����ϱ� ���� ����
	IWICImagingFactory* m_pWICFactory; //���ڴ�, ���ڴ� �� �ȼ� ���� ��ȯ��� ���� WIC(Windows Imaging Component)�� ���� ��Ҹ� ����� �� ���
	IWICFormatConverter* m_pConvertedSrcBmp;
	ID2D1Bitmap* m_pD2DBitmap;

	/// effect�� ���� ����
	ID2D1DeviceContext* m_pDeviceContext;
	ID2D1Effect* m_pGaussianBlur;

	/// bitmap �̹����� �ҷο��� �׷��� ���� 
	// ImageLoader* m_pImageLoader;

	/// D2D ������ ����ϱ� ���� ���� 
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pBrush;
	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1SolidColorBrush* m_pGreenBrush;
	ID2D1SolidColorBrush* m_pYellowBrush;
	ID2D1SolidColorBrush* m_pFontBrush;

	/// �浹�ڽ� ����
	CircleCollision* m_pCCollision;
	BoxCollision* m_pAABB;

	/// ������Ʈ ��ȯ�ϱ� ���� ����
	Transform* m_pTransform;

	/// �������� ī�޶� ��Ʈ��������Ʈ���� (Camera View Transform Matrix = ī�޶� ��ü Transform�� ����ȯ)
	D2D1::Matrix3x2F m_ViewTM;

private:

	/// �׷��� ���� �ʱ�ȭ �Լ�
	HRESULT CreateFactory();
	HRESULT CreateGraphicsResources(); // rendertarget, brush ����
	HRESULT CreateTextResources();
	HRESULT CreateWICFactory(); // WICFatory �ʱ�ȭ

	/// ������ �������� �����ϴ� �Լ�
	void DiscardGraphicsResources();

	/// bitmap file�� �ҷ����� �Լ���
	// bitmap�� �ҷ����� �Լ��� 
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

	// cstring ���ڿ��� wcstirng���� �ٲٴ� �Լ� 
	wchar_t* ConvertCStoWCS(const char* orig);

	
	/// ���� ������ִ� �Լ�
	void CalculateLayout();

	/// �浹 üũ�ϴ� �Լ�
	void AxisAlinedBoundingBox(D2D1_RECT_F rect1, D2D1_RECT_F rect2);

public:
	const wchar_t* m_wszText;
	UINT32 m_cTextLength;

	/// ��������Ʈ�� ������ ������ ����.
	std::vector<HBSpriteSheet*> m_SpriteSheetInfos;

	/// sprite ���� ����
	int m_SpriteCount;
	int m_SpriteSheetCount;

	/// �ִϸ��̼��� ������ ���� �ʿ��� ����
	// ��������Ʈ�� ��µǴ� �ð�
	float m_FlowTime;

	// ��������Ʈ�� �󸶵��� ����� �������� ���� �ð�
	float m_DelayTime;

	// �ִϸ��̼��� �ǿ��� �ϴ� ��
	int m_FrameNum;

	D2D1_ELLIPSE m_ellipse1;
	D2D1_ELLIPSE m_ellipse2;
	D2D1_RECT_F m_rectangle1;
	D2D1_RECT_F m_rectangle2;

	float m_rectPosX;
	float m_rectPosY;

	float m_Size;

	/// getter, setter ������
	Transform* GetTransform() const { return m_pTransform; }
	D2D1::Matrix3x2F GetViewTM() const { return m_ViewTM; }

public:
	// factory �ʱ�ȭ �Լ�
	void Initialize(HWND hWnd);

	// ���� ���� ������ ������Ʈ
	void Update(D2D1::Matrix3x2F viewTM/*, D2D1::Matrix3x2F projectionTM*/);

	// �׸��⿡ �ʿ��� �Լ� 
	void BeginRender();
	void OnRender();		// �׷��ִ� �Լ� 
	void EndRender();

	void OnDeviceLost();	// Ư�� ����(â ũ�� ����, Alt+Tab)�� ����Ÿ���� �ҽǵǾ��� �� ȣ���� ��


	void SetTransformLocal();	// Ʈ�������� ���ñ�������
	void SetTransformView();	// ī�޶� ���� ��Ų ���·�


	// ������ǥ���� ����ǥ���� ���� �׸���.  
	void DrawLine(float startX, float startY, float endX,  float endY);
	
	// posX, posY ���� �������� radius��ŭ ���� �׸���. 
	void DrawEllipse(float posX, float posY, float radius);

	// posX, posY ���� �������� radius��ŭ ���簢���� �׸���. 
	void DrawRectangle(float posX, float posY, float radius);

	// posX, posY ���� �������� width, height��ŭ ���簢���� �׸���. 
	void DrawRectangle(float posX, float posY, float width, float height);
	void DrawRectangle(D2D1_RECT_F rect, D2D1::Matrix3x2F worldTM = D2D1::Matrix3x2F::Identity(), bool localSpace = false);
	void DrawRectangleR(D2D1_RECT_F rect, D2D1::Matrix3x2F worldTM = D2D1::Matrix3x2F::Identity(), bool localSpace = false);
	void DrawRectangleY(D2D1_RECT_F rect, D2D1::Matrix3x2F worldTM = D2D1::Matrix3x2F::Identity(), bool localSpace = false);


	/// ����� �����͸� ���� �Լ���

	// �ڽ��� ��������Ʈ �̹�����ŭ �浹�ڽ��� �׷��ִ� �Լ�
	void DrawCollisionRect_Dev(float posX, float posY, int Sheetindex, int Spriteindex, bool ScreenSpace = false);

	// ���ϴ� ��ǥ�� �ؽ�Ʈ�� ����. 
	void DrawText(float posX, float posY, const char* pch, ...);

	// ��������Ʈ�� �׷��ִ� �Լ� 
	void DrawBitmap();
	void DrawSprite(int _sheetIndex, int _spriteIndex, int _posX, int _posY);
	void DrawSprite(Transform* pTransform, int _sheetIndex, int _spriteIndex);

	// ��������Ʈ�� �����ϴ� �Լ�
	HBSprite* GetSprite(int sheetIndex, int spriteIndex);
	D2D1_RECT_F GetSpriteRect(int sheetIndex, int spriteIndex);


	/// file�� �ּҿ� ����������, ������ ���� ���ͼ� �����Ѵ�. 
	int LoadSpriteSheet(const char* filePath, int frameCount); // ��������Ʈ ��Ʈ �ε�
	int LoadSpriteSheet(const wchar_t* filePath, int frameCount);

	// sprite ������ HBSprite* �� �־��ִ� �Լ�
	HBSpriteSheet* SpriteSheetInfo(int index, int width, int height, int frameCount);
	void SpriteSheetInfo(int width, int height, int frameCount);
	void SpriteSheetInfo(ID2D1Bitmap* Bitmap, int width, int height, int frameCount);

	// sheet�� ���ϴ� ũ�� ��ŭ �ڸ��� �Լ�
	HBSprite* SplitSpriteSheet(int x, int y, int width, int height);

	// m_SpriteSheetInfos�� �ִ� HBSpriteSheet�� �������� �Լ�. 
	HBSpriteSheet* GetSpriteSheetInfo(int _sheetIndex);

	void PlayAnimation(GameObject* _object, int _sheetIndex, int* _spriteIndex);

	// Move �Լ���
	void EllipseMove(D2D1_ELLIPSE ellipse, float posX, float posY);

	void RectangleMove(D2D1_RECT_F rect, float posX, float posY);

	// effect �Լ� 
	void SetGaussianBlurEffect(ID2D1Bitmap** pBitmap);



	/// ��������/�浹����
	bool Collision_AABB(D2D1_RECT_F rt1, D2D1_RECT_F rt2);


};


