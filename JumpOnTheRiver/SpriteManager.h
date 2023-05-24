#pragma once

class DesireD2D;


/// <summary>
/// 모든 이미지를 업로드 한다. 생성 및 제거
/// 
/// </summary>
class SpriteManager
{
public:
	SpriteManager();
	SpriteManager(DesireD2D* pEngine);
	~SpriteManager();

private:
	DesireD2D* m_pEngine;

public:
	// 게임에 필요한 모든 resource를 가져와서 엔진에 넣어준다. 
	void SpriteLoad();

	// 가져온 이미지들을 제거한다. 
	void Release();

};

