#include "pch.h"
#include "HBSprite.h"

HBSpriteSheet::HBSpriteSheet()
	: m_SheetIndex(0), m_pBitmapAddress(nullptr),
	m_Size({ 0, 0 }), m_Pivot({ 0,0 }), m_FrameCount(0),
	m_PosInSheet({ 0, 0 }), m_ScrSize({ 0,0 })
{

}

HBSpriteSheet::HBSpriteSheet(int Index, HBVector2<int> _size, HBVector2<int> _pivot, int frameCount)
	:m_SheetIndex(Index), m_pBitmapAddress(nullptr),
	m_Size(_size), m_Pivot(_pivot), m_FrameCount(frameCount),
	m_PosInSheet({ 0, 0 }), m_ScrSize({ 0,0 })
{

}

HBSpriteSheet::HBSpriteSheet(int _index, int width, int height, int pivotX, int pivotY, int frameCount)
	: m_SheetIndex(_index), m_pBitmapAddress(nullptr),
	m_Size({ width, height }), m_Pivot({ pivotX, pivotY }), m_FrameCount(frameCount),
	m_PosInSheet({ 0, 0 }), m_ScrSize({ 0,0 })
{
}

HBSpriteSheet::HBSpriteSheet(int width, int height, int pivotX, int pivotY, int frameCount)
	: m_SheetIndex(0), m_pBitmapAddress(nullptr),
	m_Size({ width, height }), m_Pivot({ pivotX, pivotY }), m_FrameCount(frameCount),
	m_PosInSheet({ 0, 0 }), m_ScrSize({ 0,0 })
{

}

HBSpriteSheet::~HBSpriteSheet()
{

	int _vecMax =  m_Sprites.size();

	for (int i = 0; i < _vecMax; i++)
	{
		delete m_Sprites.at(i);
	}

	m_ScrSize = { NULL, NULL };
	m_PosInSheet = { NULL, NULL };
	m_FrameCount = NULL;
	m_Pivot = { NULL, NULL };
	m_Size = { NULL, NULL };

	m_SheetIndex = NULL;
}
