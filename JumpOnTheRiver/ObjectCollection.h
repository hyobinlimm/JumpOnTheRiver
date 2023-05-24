#pragma once
#include <vector>
#include "HBVector2.h"

/// <summary>
///  ������Ʈ���� �����ϰ� �ִٰ� ȭ�鿡 �׷����� ���� 
///  ON, OFF ���ִ� Ŭ����
/// </summary>

class Object;

class ObjectCollection
{
public:
	ObjectCollection();
	~ObjectCollection();

private:
	// ��� ������Ʈ�� ��ġ���� �־�����. 
	// ���߿� �� ���������� ī�޶� ����� �����ؼ� ī�޶� �׸��� ���� ���Ѵ�. 
	std::vector<std::pair<HBVector2<float>, int>> m_OjectPos;

	// ī�޶� �׷����� ������Ʈ �鸸 �̹����� ���Ϳ� �־��ش�. 
	std::vector<Object*> m_OnDrawOject;

	// ī�޶� �� �׷����� ������Ʈ���� ���Ϳ� �־��ش�. 
	std::vector<Object*> m_OffDrawOject;

public:

	// �����͸� �ҷ��ͼ� �����ǰ� �̹����� �ε����� ���Ϳ� �־��ش�. 
	void PushDataFromVector();
		
};

