#pragma once
#include "GameObject.h"
#include "Matrix.h"
#include "HBVector2.h"
#include "Define.h"

class DesireD2D;

enum class OBJECT_SIDE
{
	LEFT, RIGHT, UP, DOWN,
};

/// <summary>
/// 2022 . 02. 07 Son
/// 
/// 상호 작용 가능한 오브젝트
/// 플랫폼, 박스, 가시, 트리거
/// </summary>
class Object : public GameObject
{
	/// 오브젝트가 가지고 있어야 하는 멤버 변수들
	// 
public:
	Object();
	//Object(float x, float y);
	//Object(HBVector2<float> pos);
	virtual ~Object();

public:
	// 그리기(draw) 함수
	virtual void Draw() override;

	virtual void Draw(DesireD2D* engine2D);

	// Update 함수
	virtual void Update() override;

	// 좌표
	HBVector2<float> m_pos;

	// 절대적인 인덱스
	int m_UniqueIndex;

	// 나는 누구야 / 내가 어떤 스프라이트 상태인가?
	OBJECT_TYPE m_ID;

	// 현재 그려질 스프라이트의 인덱스 (지금 몇 번째 장을 그리고 있는가?)
	int m_CurrentIndex;

public:
	void SetObjectType(OBJECT_TYPE type);
	OBJECT_TYPE GetObjectType() { return m_ID; }
	void SetSide(OBJECT_SIDE horizontal, OBJECT_SIDE vertical);

	void SetPosition(HBVector2<float> val);
	void ApplyPosToTransform();

	// 충돌감지를 스프라이트 기반으로 해 분다.
	void CreateCollisionFromSpriteInfo(DesireD2D* pEngine);


private:
	// 2D 그래픽스 엔진을 이용한 구현체
	DesireD2D* m_pEngine2D;

private:
	/// 모든 오브젝트들이 가지고 있어야 하는 것
	// 좌표
	//Position2D m_Pos;

	// 세이브 포인트 닿았나 체크
	bool m_bTriggerCheck;


	/// 충돌감지
protected:
	COLLIDER_LAYER m_ColliderLayer;
	float m_CollidedPosY;		// 충돌을 했을 때 그 오브젝트의 Y최댓값

public:
	COLLIDER_LAYER GetColliderLayer() const { return m_ColliderLayer; }
	void SetColliderLayer(COLLIDER_LAYER val) { m_ColliderLayer = val; }

	float GetCollidedPosY() const { return m_CollidedPosY; }
	void SetCollidedPosY(float val) { m_CollidedPosY = val; }


public:
	static int m_CreateIndex;
};

