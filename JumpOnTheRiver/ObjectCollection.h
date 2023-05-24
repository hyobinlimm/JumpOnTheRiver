#pragma once
#include <vector>
#include "HBVector2.h"

/// <summary>
///  오브젝트들을 보관하고 있다가 화면에 그렬줄지 말지 
///  ON, OFF 해주는 클래스
/// </summary>

class Object;

class ObjectCollection
{
public:
	ObjectCollection();
	~ObjectCollection();

private:
	// 모든 오브젝트의 위치값을 넣어주자. 
	// 나중에 이 위차값들을 카메라 값들과 연산해서 카메라에 그릴지 말지 정한다. 
	std::vector<std::pair<HBVector2<float>, int>> m_OjectPos;

	// 카메라에 그려지는 오브젝트 들만 이미지를 벡터에 넣어준다. 
	std::vector<Object*> m_OnDrawOject;

	// 카메라에 안 그려지는 오브젝트들을 벡터에 넣어준다. 
	std::vector<Object*> m_OffDrawOject;

public:

	// 데이터를 불러와서 포지션과 이미지의 인덱스를 벡터에 넣어준다. 
	void PushDataFromVector();
		
};

