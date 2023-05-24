#pragma once
#include "pch.h"

class Transform;
class Animator;
class Shape;

/// <summary>
/// ���ӿ�����Ʈ (��ƼƼ)
/// 
/// ����Ƽ�� �װ��� �ִ��� �䳻�� ��
/// 
/// 2022.02.24 LeHideLogic
/// </summary>
class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Draw() abstract;
	virtual void Update() abstract;


	// ��ȯ ����
private:
	Transform* m_pTransform;
public:
	Transform* GetTransform() const { return m_pTransform; }
	

	// �浹���� ����
public:
	// local
	D2D1_RECT_F GetCollisionBox() const { return m_CollisionBox; }
	void SetCollisionBox(D2D1_RECT_F val) { m_CollisionBox = val; }

	// world
	D2D1_RECT_F GetWorldCollisionBox() const;

	bool GetIsCollided() const { return m_IsCollided; }
	void SetIsCollided(bool val) { m_IsCollided = val; }

protected:
	bool m_IsCollided;
	D2D1_RECT_F m_CollisionBox;
};

