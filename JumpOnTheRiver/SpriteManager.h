#pragma once

class DesireD2D;


/// <summary>
/// ��� �̹����� ���ε� �Ѵ�. ���� �� ����
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
	// ���ӿ� �ʿ��� ��� resource�� �����ͼ� ������ �־��ش�. 
	void SpriteLoad();

	// ������ �̹������� �����Ѵ�. 
	void Release();

};

