#pragma once
#include <vector>
#include <d2d1.h>

#include <string>

//
#include "Define.h"

// Json 관련 헤더입니다.
#include "./rapidjson/document.h"

// 오브젝트 데이터 관련 헤더입니다.
#include "ObjectInfo.h"

// fps 관련 헤더
#include "HBTime.h"

// 키인풋 관련
#include "smartinput.h"


// 오브젝트 데이터 관련 구조체입니다.
struct ObjectInfo;

class DesireD2D;
class Object;
class CInput;
class Player;
class BackGround;
class Camera;

/// <summary>
/// 오브젝트의 생성과 소멸, 관리(찾기)를 담당한다.
/// 
/// + 오브젝트들을 그린다. 오브젝트들의 상호작용을 한다...
/// 
/// 2022.02.21 LeHideHome
/// </summary>
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();


	// 오브젝트를 생성한다.
	void Initialize(DesireD2D* engine, CInput* pKeyInput);
	
	// 오브젝트를 삭제한다.
	void Release();

	// 특정 인덱스로 부터 오브젝트를 찾는다.
	void FindObject();

	// 모든 오브젝트를 업데이트한다.
	void Update();

private:
	void Update_CollisionDetection();
	void Update_FSM_GirlShadow();
	void Update_FSM_ByInput();


public:
	// 모든 오브젝트를 그린다.
	void Render();

private:
	void Render_Debug();

public:
	// 오브젝트의 데이터를 로드합니다.
	void LoadObjectData();


private:
	// 오브젝트를 생성하는 팩토리 함수입니다.
	Object* CreateObject(ObjectInfo* info);
	// 오브젝트의 타입을 변환하는 함수입니다.
	OBJECT_TYPE ConvertIndexToObjectType(int index);

private:
	DesireD2D* m_pEngine;
	CInput* m_KeyInput;

	// 오브젝트의 데이터를 가지고 있는 변수입니다.
	std::vector<ObjectInfo*> m_ObjectInfos;

	// 오브젝트의 변수를 가진다.
	std::vector<Object*> m_Objects;

	// 오브젝트들의 포지션을 가지고 있는다. 
	//std::vector<std::pair<Object*, HBVector2<float>>> m_ObjectPos;

	// 소녀의 지금 키 입력이 뭔지 출력
	std::string m_GirlKeyState;

	// 카메라 정보 위치 정보
	std::string m_CameraPos;

	// 카메라 트렌스폼
	std::string m_CameraTransScale;
	std::string m_CameraTransRotatation;
	std::string m_CameraTransPos;

	// 카메라 ViewTM
	std::string m_CameraViewTM;

	// 오브젝트의 갯수
	int m_ObjectCount;

	// fps 변수
	HBTime* m_Timer;

	// fps 담기용 변수
	float m_nowTimer;


	/// 특별히 따로 컨트롤 해 줘야 하는 오브젝트들의 참조(포인터 사본)

	// 소녀 플레이어1
	Player* m_GirlPlayer;

	// 그림자 플레이어2
	Player* m_ShadowPlayer;

	// 카메라
	Camera* m_Camera;

public:
	SmartInput* m_SmartInput;

	bool isDubug = false;

public:
	D2D1::Matrix3x2F GetViewTM();
};

