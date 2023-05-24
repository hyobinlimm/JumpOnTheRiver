#pragma once
#include <vector>
#include <d2d1.h>

#include <string>

//
#include "Define.h"

// Json ���� ����Դϴ�.
#include "./rapidjson/document.h"

// ������Ʈ ������ ���� ����Դϴ�.
#include "ObjectInfo.h"

// fps ���� ���
#include "HBTime.h"

// Ű��ǲ ����
#include "smartinput.h"


// ������Ʈ ������ ���� ����ü�Դϴ�.
struct ObjectInfo;

class DesireD2D;
class Object;
class CInput;
class Player;
class BackGround;
class Camera;

/// <summary>
/// ������Ʈ�� ������ �Ҹ�, ����(ã��)�� ����Ѵ�.
/// 
/// + ������Ʈ���� �׸���. ������Ʈ���� ��ȣ�ۿ��� �Ѵ�...
/// 
/// 2022.02.21 LeHideHome
/// </summary>
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();


	// ������Ʈ�� �����Ѵ�.
	void Initialize(DesireD2D* engine, CInput* pKeyInput);
	
	// ������Ʈ�� �����Ѵ�.
	void Release();

	// Ư�� �ε����� ���� ������Ʈ�� ã�´�.
	void FindObject();

	// ��� ������Ʈ�� ������Ʈ�Ѵ�.
	void Update();

private:
	void Update_CollisionDetection();
	void Update_FSM_GirlShadow();
	void Update_FSM_ByInput();


public:
	// ��� ������Ʈ�� �׸���.
	void Render();

private:
	void Render_Debug();

public:
	// ������Ʈ�� �����͸� �ε��մϴ�.
	void LoadObjectData();


private:
	// ������Ʈ�� �����ϴ� ���丮 �Լ��Դϴ�.
	Object* CreateObject(ObjectInfo* info);
	// ������Ʈ�� Ÿ���� ��ȯ�ϴ� �Լ��Դϴ�.
	OBJECT_TYPE ConvertIndexToObjectType(int index);

private:
	DesireD2D* m_pEngine;
	CInput* m_KeyInput;

	// ������Ʈ�� �����͸� ������ �ִ� �����Դϴ�.
	std::vector<ObjectInfo*> m_ObjectInfos;

	// ������Ʈ�� ������ ������.
	std::vector<Object*> m_Objects;

	// ������Ʈ���� �������� ������ �ִ´�. 
	//std::vector<std::pair<Object*, HBVector2<float>>> m_ObjectPos;

	// �ҳ��� ���� Ű �Է��� ���� ���
	std::string m_GirlKeyState;

	// ī�޶� ���� ��ġ ����
	std::string m_CameraPos;

	// ī�޶� Ʈ������
	std::string m_CameraTransScale;
	std::string m_CameraTransRotatation;
	std::string m_CameraTransPos;

	// ī�޶� ViewTM
	std::string m_CameraViewTM;

	// ������Ʈ�� ����
	int m_ObjectCount;

	// fps ����
	HBTime* m_Timer;

	// fps ���� ����
	float m_nowTimer;


	/// Ư���� ���� ��Ʈ�� �� ��� �ϴ� ������Ʈ���� ����(������ �纻)

	// �ҳ� �÷��̾�1
	Player* m_GirlPlayer;

	// �׸��� �÷��̾�2
	Player* m_ShadowPlayer;

	// ī�޶�
	Camera* m_Camera;

public:
	SmartInput* m_SmartInput;

	bool isDubug = false;

public:
	D2D1::Matrix3x2F GetViewTM();
};

