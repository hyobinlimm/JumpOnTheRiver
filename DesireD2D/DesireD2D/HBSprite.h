#pragma once
#include <vector>

/// <summary>
/// ��������Ʈ ������ ������ �ִ´�. 
/// 
/// 2022.02.08 hyobin
/// </summary>

// ���� �ִ� �͵��� ��������Ʈ �Ŵ��� ������ �� ũ�� ������ �� �� ����. 

class HBSprite;

class HBSpriteSheet
{
public:
	HBSpriteSheet();
	// ��������Ʈ�� �̹����� �޾ƿ���.
	HBSpriteSheet(int _index, HBVector2<int> _size, HBVector2<int> _pivot, int frameCount);
	HBSpriteSheet(int _index, int width, int height, int pivotX, int pivotY, int frameCount);
	HBSpriteSheet(int width, int height, int pivotX, int pivotY, int frameCount);

	~HBSpriteSheet();

	// ��������Ʈ �ε���
	int m_SheetIndex;

	ID2D1Bitmap* m_pBitmapAddress;

	// ��������Ʈ ���� ������(����, ����) 
	HBVector2<int> m_Size;

	// ��������Ʈ ���� ��ǥ
	HBVector2<int> m_Pivot;

	// ��� �� ������ ��
	int m_FrameCount;

	// ��������Ʈ ��Ʈ ���� ��ġ
	HBVector2<int> m_PosInSheet;

	// ������Ʈ�� �������κ��� ȭ�鿡 �׷��� ũ�� 
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