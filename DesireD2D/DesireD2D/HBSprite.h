#pragma once
#include <vector>

/// <summary>
/// 스프라이트 정보만 가지고 있는다. 
/// 
/// 2022.02.08 hyobin
/// </summary>

// 여기 있는 것들을 스프라이트 매니저 단으로 더 크게 나눠야 할 것 같다. 

class HBSprite;

class HBSpriteSheet
{
public:
	HBSpriteSheet();
	// 스프라이트의 이미지를 받아오자.
	HBSpriteSheet(int _index, HBVector2<int> _size, HBVector2<int> _pivot, int frameCount);
	HBSpriteSheet(int _index, int width, int height, int pivotX, int pivotY, int frameCount);
	HBSpriteSheet(int width, int height, int pivotX, int pivotY, int frameCount);

	~HBSpriteSheet();

	// 스프라이트 인덱스
	int m_SheetIndex;

	ID2D1Bitmap* m_pBitmapAddress;

	// 스프라이트 원본 사이즈(가로, 세로) 
	HBVector2<int> m_Size;

	// 스프라이트 중점 좌표
	HBVector2<int> m_Pivot;

	// 재생 될 프레임 수
	int m_FrameCount;

	// 스프라이트 시트 내의 위치
	HBVector2<int> m_PosInSheet;

	// 오브젝트의 중점으로부터 화면에 그려질 크기 
	HBVector2<float> m_ScrSize;

	std::vector<HBSprite*> m_Sprites;

};

class HBSprite
{
public:
	HBSprite()
		: x(0), y(0), width(0), height(0)
	{

	}

	HBSprite(float _x, float _y, float _width, float _height)
		: x(_x), y(_y), width(_width), height(_height)
	{

	}

	HBSprite(int _x, int _y, int _width, int _height)
		: x((float)_x), y((float)_y), width((float)_width), height((float)_height)
	{

	}

	~HBSprite()
	{
		x = NULL;
		y = NULL;
		width = NULL;
		height = NULL;
	};

	float x, y;

	float width, height;
};