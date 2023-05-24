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
/// ��ȣ �ۿ� ������ ������Ʈ
/// �÷���, �ڽ�, ����, Ʈ����
/// </summary>
class Object : public GameObject
{
	/// ������Ʈ�� ������ �־�� �ϴ� ��� ������
	// 
public:
	Object();
	//Object(float x, float y);
	//Object(HBVector2<float> pos);
	virtual ~Object();

public:
	// �׸���(draw) �Լ�
	virtual void Draw() override;

	virtual void Draw(DesireD2D* engine2D);

	// Update �Լ�
	virtual void Update() override;

	// ��ǥ
	HBVector2<float> m_pos;

	// �������� �ε���
	int m_UniqueIndex;

	// ���� ������ / ���� � ��������Ʈ �����ΰ�?
	OBJECT_TYPE m_ID;

	// ���� �׷��� ��������Ʈ�� �ε��� (���� �� ��° ���� �׸��� �ִ°�?)
	int m_CurrentIndex;

public:
	void SetObjectType(OBJECT_TYPE type);
	OBJECT_TYPE GetObjectType() { return m_ID; }
	void SetSide(OBJECT_SIDE horizontal, OBJECT_SIDE vertical);

	void SetPosition(HBVector2<float> val);
	void ApplyPosToTransform();

	// �浹������ ��������Ʈ ������� �� �д�.
	void CreateCollisionFromSpriteInfo(DesireD2D* pEngine);


private:
	// 2D �׷��Ƚ� ������ �̿��� ����ü
	DesireD2D* m_pEngine2D;

private:
	/// ��� ������Ʈ���� ������ �־�� �ϴ� ��
	// ��ǥ
	//Position2D m_Pos;

	// ���̺� ����Ʈ ��ҳ� üũ
	bool m_bTriggerCheck;


	/// �浹����
protected:
	COLLIDER_LAYER m_ColliderLayer;
	float m_CollidedPosY;		// �浹�� ���� �� �� ������Ʈ�� Y�ִ�

public:
	COLLIDER_LAYER GetColliderLayer() const { return m_ColliderLayer; }
	void SetColliderLayer(COLLIDER_LAYER val) { m_ColliderLayer = val; }

	float GetCollidedPosY() const { return m_CollidedPosY; }
	void SetCollidedPosY(float val) { m_CollidedPosY = val; }


public:
	static int m_CreateIndex;
};

