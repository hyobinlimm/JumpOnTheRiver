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
/// �̹��� ��θ� �޾ƿ�
/// �޾ƿ� �̹����� ȭ�鿡 ���
/// 
/// 22.02.09. hyobin
/// </summary>

class ImageLoader : public TemplateSingleton<ImageLoader>
{
public:
	ImageLoader();
	~ImageLoader();

private:
	/// bitmap�� ����ϱ� ���� ����
	//IWICImagingFactory* m_pWICFactory; //���ڴ�, ���ڴ� �� �ȼ� ���� ��ȯ��� ���� WIC(Windows Imaging Component)�� ���� ��Ҹ� ����� �� ���
	//IWICFormatConverter* m_pConvertedSrcBmp;
	//ID2D1Bitmap* m_pD2DBitmap;

	/// bitmap�� �׸��� ���� �˷��� ���� 
	ID2D1HwndRenderTarget* m_pRenderTarget;

	/// ������ ������ִ� ����
	Shape* m_pShape;

	// ��������Ʈ�� ��µǴ� �ð�
	float m_FlowTime;

	// ��������Ʈ�� �󸶵��� ����� �������� ���� �ð�
	float m_DelayTime;

	// �׷����� ��������Ʈ�� �ε��� 
	int m_CurrentIndex;

	// �ִϸ��̼��� �ǿ��� �ϴ� ��
	int m_FrameNum;

public:
	/// sprite ���� ����
	int m_SpriteCount;
	int m_SpriteSheetCount;

	/// ��������Ʈ�� ������ ������ ����.
	std::vector<HBSpriteSheet*> m_SpriteSheetInfos;	

private:
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

public:

	/// WICFatory �ʱ�ȭ
	//HRESULT CreateWICFactory(ID2D1HwndRenderTarget* pRenderTarget);
	void initialize(ID2D1HwndRenderTarget* pRenderTarget);

	// sprite ���� �Լ���
	//int LoadSpriteSheet(const char* filePath, int frameCount); // ��������Ʈ ��Ʈ �ε�
	//int LoadSpriteSheet(const wchar_t* filePath, int frameCount);

	// �̹��� �ε��ϴ� �Լ�
	void LoadImageResource(ID2D1HwndRenderTarget* m_pRenderTarget);

	// sprite ������ HBSprite* �� �־��ִ� �Լ�
	// HBSpriteSheet* SpriteSheetInfo(int index, int width, int height, int frameCount);
	// void SpriteSheetInfo(int width, int height, int frameCount);
	// void SpriteSheetInfo(ID2D1Bitmap* Bitmap, int width, int height, int frameCount);

	// sheet�� ���ϴ� ũ�� ��ŭ �ڸ��� �Լ�
	// HBSprite* SplitSpriteSheet(int x, int y, int width, int height);

	//void DrawBitmap();
	//void DrawSprite(int _sheetIndex, int _spriteIndex, int _posX, int _posY, D2D1::Matrix3x2F _viewTM);
	//void DrawSprite(GameObject* _object, int _sheetIndex, int _spriteIndex, D2D1::Matrix3x2F _viewTM);

	// m_SpriteSheetInfos�� �ִ� HBSpriteSheet�� �������� �Լ�. 
	HBSpriteSheet* GetSpriteSheetInfo(int _sheetIndex);

	void PlayAnimation(GameObject* _object, int _sheetIndex, D2D1::Matrix3x2F _viewTM);

	// �̹����� �����ϴ� �Լ�
	void Release();
};

