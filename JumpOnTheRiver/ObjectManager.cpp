#include "ObjectManager.h"

#include "DesireD2D.h"
#include "Object.h"
#include "Player.h"
#include "BackGround.h"
#include "Camera.h"
#include "Transform.h"
#include "Define.h"
#include "CInput.h"
#include <string>


ObjectManager::ObjectManager()
	: m_pEngine(nullptr), m_KeyInput(nullptr), m_ObjectCount(0),
	m_Timer(nullptr), m_nowTimer(0.f),
	m_GirlPlayer(nullptr), m_ShadowPlayer(nullptr), m_Camera(nullptr)
{
	m_ObjectInfos.clear();
}

ObjectManager::~ObjectManager()
{
	for (size_t i = 0; i < m_ObjectInfos.size(); i++)
	{
		delete m_ObjectInfos[i];
	}

	m_ObjectInfos.clear();

	const int ObjectSize = m_Objects.size();
	for (int i = 0; i < ObjectSize; i++)
	{
		delete m_Objects[i];
	}
}

#pragma region 오브젝트 데이터 로드

// 오브젝트 데이터를 로드합니다.
void ObjectManager::LoadObjectData()
{
	rapidjson::GenericDocument<rapidjson::UTF16<>> Json;

	FILE* fp = nullptr;
	fopen_s(&fp, "map.json", "rb");

	if (fp != nullptr)
	{
		fseek(fp, 0, SEEK_END);
		int nFileSize = ftell(fp);

		fseek(fp, 2, SEEK_SET);

		wchar_t* str = new wchar_t[nFileSize]();

		int size = sizeof(wchar_t);
		fread(str, size, nFileSize, fp);
		Json.Parse(str);

		delete[] str;
		fclose(fp);
	}
	else
	{
		return;
	}

	rapidjson::GenericValue< rapidjson::UTF16<>>& infoArray = Json[L"Info"].GetArray();

	// 오브젝트 데이터를 저장합니다.
	ObjectInfo* pObjectInfo = nullptr;

	for (size_t i = 0; i < infoArray.Size(); i++)
	{
		pObjectInfo = new ObjectInfo();
		pObjectInfo->index = infoArray[i][L"Index"].GetInt();
		pObjectInfo->x = infoArray[i][L"X"].GetInt();
		pObjectInfo->y = infoArray[i][L"Y"].GetInt();

		m_ObjectInfos.push_back(pObjectInfo);
	}
}

// 오브젝트를 생성합니다.
Object* ObjectManager::CreateObject(ObjectInfo* info)
{
	Object* _newObject = new Object();
	_newObject->SetPosition({ (float)info->x, (float)info->y });
	_newObject->SetObjectType(this->ConvertIndexToObjectType(info->index));

	return _newObject;
}

// 오브젝트의 타입을 변환합니다.
OBJECT_TYPE ObjectManager::ConvertIndexToObjectType(int index)
{
	switch (index)
	{
		case 0: return OBJECT_TYPE::cloud1_100x40_object;
		case 1: return OBJECT_TYPE::cloud1shadow_100x40_object;
		case 2: return OBJECT_TYPE::cloud2_150x40_object;
		case 3: return OBJECT_TYPE::cloud2shadow_150x40_object;
		case 4: return OBJECT_TYPE::cloud3_250x45_object;
		case 5: return OBJECT_TYPE::cloud3shadow_250x45_object;
		case 6: return OBJECT_TYPE::rock1_75x65_object;
		case 7: return OBJECT_TYPE::rock1shadow_75x65_object;
		case 8: return OBJECT_TYPE::rock2_150x65_object;
		case 9: return OBJECT_TYPE::rock2shadow_150x65_object;
		case 10: return OBJECT_TYPE::rock3_100x215_object;
		case 11: return OBJECT_TYPE::rock3shadow_100x215_object;
		case 12: return OBJECT_TYPE::rockmix1_object;
		case 13: return OBJECT_TYPE::rockmix1shadow_object;
		case 14: return OBJECT_TYPE::rockmix2_object;
		case 15: return OBJECT_TYPE::rockmix2shadow_object;
		case 16: return OBJECT_TYPE::rockmix3_object;
		case 17: return OBJECT_TYPE::rockmix3shadow_object;
		case 18: return OBJECT_TYPE::object_box;
		case 19: return OBJECT_TYPE::object_box_shadow;
		case 20: return OBJECT_TYPE::object_vine;
		case 21: return OBJECT_TYPE::object_doll;
		case 22: return OBJECT_TYPE::object_star;

		default: assert(false);
			break;
	}

	return OBJECT_TYPE::background_sky;
}

#pragma endregion

void ObjectManager::Initialize(DesireD2D* pEngine, CInput* pKeyInput)
{
	LoadObjectData();

	// 그래픽스 엔진
	m_pEngine = pEngine;

	// 키 입력을 담당하는 객체 참조
	m_KeyInput = pKeyInput;

	m_SmartInput = new SmartInput();

	/// 오브젝트 생성

	// 소녀
	Player* girl = new Player(PLAYER_TYPE::GIRL, ConstValue::PositiveY);
	girl->SetPosition({ ConstValue::StartPosX, ConstValue::PositiveY - 100.0f });
	girl->SetSide(OBJECT_SIDE::RIGHT, OBJECT_SIDE::UP);
	girl->SetObjectType(OBJECT_TYPE::girl_idle);
	girl->SetCollisionBox({ -25.f, 0.f, 25.f, 57.5f });
	girl->SetColliderLayer(COLLIDER_LAYER::PLAYER);
	girl->SetGravity(GRAVITY);
	girl->SetJumpPower(JUMP_POWER);
	girl->m_IdleSprite = OBJECT_TYPE::girl_idle;
	girl->m_IdleAirSprite = OBJECT_TYPE::girl_jump;
	girl->m_WalkSprite = OBJECT_TYPE::girl_walk;
	girl->m_DownSprite = OBJECT_TYPE::girl_crouch;
	girl->m_HoldSprite = OBJECT_TYPE::girl_push;

	m_GirlPlayer = girl;
	m_Objects.push_back(girl);

	// 그림자
	Player* shadow = new Player(PLAYER_TYPE::SHADOW, ConstValue::NegativeY);
	shadow->SetPlayerType(PLAYER_TYPE::SHADOW);
	shadow->SetPosition({ ConstValue::StartPosX, ConstValue::NegativeY + 5 });
	shadow->SetSide(OBJECT_SIDE::RIGHT, OBJECT_SIDE::DOWN);
	shadow->SetObjectType(OBJECT_TYPE::shadow_idle);
	shadow->SetCollisionBox({ -25.f, 0.f, 25.f, 54.f });
	shadow->SetColliderLayer(COLLIDER_LAYER::PLAYER);
	shadow->SetGravity(-GRAVITY);
	shadow->SetJumpPower(-JUMP_POWER);
	shadow->m_IdleSprite = OBJECT_TYPE::shadow_idle;
	shadow->m_IdleAirSprite = OBJECT_TYPE::shadow_jump;
	shadow->m_WalkSprite = OBJECT_TYPE::shadow_walk;
	shadow->m_DownSprite = OBJECT_TYPE::shadow_idle;
	shadow->m_HoldSprite = OBJECT_TYPE::shadow_push;

	m_ShadowPlayer = shadow;
	m_Objects.push_back(shadow);

#pragma region 오브젝트 생성
	// 로드한 데이터로 오브젝트를 생성합니다.
	for (size_t i = 0; i < m_ObjectInfos.size(); i++)
	{
		Object* _newObject = CreateObject(m_ObjectInfos[i]);
		_newObject->CreateCollisionFromSpriteInfo(pEngine);
		_newObject->SetColliderLayer(COLLIDER_LAYER::STATIC_OBJECT);
		m_Objects.push_back(_newObject);
	}
#pragma endregion

	// 지면
 	Object* _groundBox = new Object();
 	_groundBox->SetPosition({ 960, 540 });
 	_groundBox->GetTransform()->SetScale({ 1, 1 });
 	_groundBox->m_ID = OBJECT_TYPE::background_center;
 	_groundBox->SetCollisionBox({ -4000.f, -25.f, 5000.f, 25.f });
 	_groundBox->SetColliderLayer(COLLIDER_LAYER::GROUND);
 	m_Objects.push_back(_groundBox);

	// 구름 배경
	BackGround* backGroundCloud = new BackGround();
	backGroundCloud->SetPosition({ 960, 540 });
	backGroundCloud->SetSide(OBJECT_SIDE::RIGHT, OBJECT_SIDE::UP);
	backGroundCloud->SetObjectType(OBJECT_TYPE::background_cloud);
	m_Objects.push_back(backGroundCloud);

	// 가운데 바닥
	Object* backgroundcenter = new Object();
	backgroundcenter->GetTransform()->SetPosition({ 960, 540 });
	backgroundcenter->GetTransform()->SetScale({ 1, 1 });
	backgroundcenter->m_ID = OBJECT_TYPE::background_center;
	m_Objects.push_back(backgroundcenter);

	// sky 배경화면
	Object* backGroundSky = new Object();
	backGroundSky->GetTransform()->SetPosition({ 960, 540 });
	backGroundSky->GetTransform()->SetScale({ 1, 1 });
	backGroundSky->m_ID = OBJECT_TYPE::background_sky;
	m_Objects.push_back(backGroundSky);

	// river 배경화면
	Object* backGroundRiver = new Object();
	backGroundRiver->GetTransform()->SetPosition({ 960, 540 });
	backGroundRiver->GetTransform()->SetScale({ 1, 1 });
	backGroundRiver->m_ID = OBJECT_TYPE::background_river;
	m_Objects.push_back(backGroundRiver);

	// 카메라
	m_Camera = new Camera();
	m_Camera->GetTransform()->SetScale({ 1, 1 });
	m_Objects.push_back(m_Camera);

	/// 리소스들의 값 초기화

}

void ObjectManager::Release()
{
	// 오브젝트를 삭제한다.
}

void ObjectManager::FindObject()
{
	// 특정 인덱스로부터 오브젝트를 찾는다.
}

void ObjectManager::Update()
{
	// 카메라 정보를 갱신한다.
	m_Camera->UpdateCoordinate(m_GirlPlayer);

	// 특별한 오브젝트 (소녀-그림자)간의 연관관계 처리
	Update_FSM_GirlShadow();

	// keyinput에 따른 캐릭터의 상태 전환
	Update_FSM_ByInput();

	/// 충돌감지
	Update_CollisionDetection();

	// 모든 오브젝트들을 갱신한다.
	for (int i = m_Objects.size() - 1; 0 <= i; i--)
	{
		m_Objects.at(i)->Update();
	}
}

void ObjectManager::Update_CollisionDetection()
{
	for (Object* pObject : m_Objects)
	{
		pObject->SetIsCollided(false);
	}

	for (Object* pMyObject : m_Objects)
	{
		for (Object* pTargetObject : m_Objects)
		{
			// 같은 오브젝트는 하지 않는다.
			if (pMyObject->m_UniqueIndex == pTargetObject->m_UniqueIndex) continue;

			// 소녀-지면, 모든 오브젝트, 상자
			if (pMyObject->GetColliderLayer() == COLLIDER_LAYER::PLAYER
				|| pMyObject->GetColliderLayer() == COLLIDER_LAYER::BOX)
			{
				// 모두 가능
			}
			else if (pMyObject->GetColliderLayer() == COLLIDER_LAYER::STATIC_OBJECT
				|| pMyObject->GetColliderLayer() == COLLIDER_LAYER::GROUND)
			{
				// 아무것도 충돌하지 않는다.
				continue;
			}

			// 타겟 종류에 따라 충돌감지
			if (m_pEngine->Collision_AABB(pMyObject->GetWorldCollisionBox(),
				pTargetObject->GetWorldCollisionBox()) == true)
			{
				pMyObject->SetIsCollided(true);
				pTargetObject->SetIsCollided(true);

				pMyObject->SetCollidedPosY(pMyObject->GetWorldCollisionBox().top);

				if (pMyObject->m_UniqueIndex == 1)
				{
					pMyObject->SetCollidedPosY(pMyObject->GetWorldCollisionBox().bottom);
				}
			}
		}
	}
}

/// <summary>
/// 특별한 오브젝트 (소녀-그림자)간의 연관관계 처리
/// FSM이 있어야 한다.
/// </summary>
void ObjectManager::Update_FSM_GirlShadow()
{
	// 기본적으로 둘 중 하나가 못움직이면, 다른 것에도 적용이 된다.
	// 소녀가 앉아 있다면, 그림자만 움직인다.
}

void ObjectManager::Update_FSM_ByInput()
{
	m_GirlPlayer->FSM(m_KeyInput->m_LeftRight, m_KeyInput->m_JumpDown, m_KeyInput->m_Hold);
	m_ShadowPlayer->FSM(m_KeyInput->m_LeftRight, m_KeyInput->m_JumpDown, m_KeyInput->m_Hold);

}

void ObjectManager::Render()
{
	// 그리기 순서를 정해서 그림을 그리는 방법:
	// 
	// A. 생성을 잘~ 하고, 역순으로 그림
	// B. 렌더링 큐를 만들고, 그것에 따라서 정렬(sortOrder)

	/// A
	// 현재 씬을 그려준다. (카메라가 확정적으로 업데이트 되었다고 가정)
	for (int i = m_Objects.size() - 1; 0 <= i; i--)
	{
		m_Objects.at(i)->Draw(m_pEngine);
		//m_Objects[i]->Draw(engine);
	}

	/// B
	/*
	// 1. 렌더링 큐에 따라서 Sort

	// 2. 모두 Draw호출
	for (Object* _pNowObject : m_Objects)
	{
		_pNowObject->Draw(engine);
	}
	*/

	// 디버그 데이터를 출력한다.

	 Render_Debug();
}


void ObjectManager::Render_Debug()
{
	// 소녀 포지션
	//m_GirlPlayer->GetTransform()->GetPosition();
	//m_GirlState.c_str();
	//m_GirlPos = std::to_string((m_GirlPlayer->m_pos.m_x));
	//m_GirlPos.append(std::to_string(m_GirlPlayer->m_pos.m_y));
	//m_GirlState.c_str();

	// 캐릭터 포지션 debug
	//engine->DrawText(-140, 165, m_GirlState.c_str());
	//engine->DrawText(-140, 185, m_GirlPos.c_str());
	m_pEngine->DrawText(-140, 205, m_GirlKeyState.c_str());



	// 카메라 포지션
	m_CameraPos = "카메라 좌표:" + std::to_string((m_Camera->m_pos.m_x)) + " ";
	m_CameraPos.append(std::to_string(m_Camera->m_pos.m_y));

	// 카메라 트랜스폼(Scale, Rotation) 스케일이랑 회전 안 주는데 알 필요가 있나요?
	//m_CameraTransScale = std::to_string(m_Camera->GetTransform()->GetScale().m_x);

	// 카메라 viewTM
	m_CameraViewTM = "ViewTM 11" + std::to_string(m_Camera->GetViewTM()._11) + "\n";
	m_CameraViewTM += "ViewTM 12" + std::to_string(m_Camera->GetViewTM()._12) + "\n";
	m_CameraViewTM += "ViewTM 21" + std::to_string(m_Camera->GetViewTM()._21) + "\n";
	m_CameraViewTM += "ViewTM 22" + std::to_string(m_Camera->GetViewTM()._22) + "\n";
	m_CameraViewTM += "ViewTM 31" + std::to_string(m_Camera->GetViewTM()._31) + "\n";
	m_CameraViewTM += "ViewTM 32" + std::to_string(m_Camera->GetViewTM()._32) + "\n";

	// 오브젝트 갯수
	m_ObjectCount = m_Objects.size();

	// 카메라 포지션
	m_pEngine->DrawText(-100, 20, m_CameraPos.c_str()/* "카메라 : %d %d", m_Camera->m_pos.m_x, m_Camera->m_pos.m_y*/);

	// 카메라 viewTM
	m_pEngine->DrawText(-120, 110, m_CameraViewTM.c_str());

	// 오브젝트 갯수 출력
	m_pEngine->DrawTextW(-140, 225, "오브젝트 갯수: %d", m_ObjectCount);

	// FPS 가져오기
	m_nowTimer = (float)HBTime::GetInstance()->GetFPS();

	// FPS 출력
	m_pEngine->DrawText(-140, 245, "FPS : %f", m_nowTimer);
}

D2D1::Matrix3x2F ObjectManager::GetViewTM()
{
	return m_Camera->GetViewTM();
}

