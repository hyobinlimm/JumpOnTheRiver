#pragma once

#include "IScene.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Object.h"
#include "ObjectManager.h"

class ObjectManager;
class Object;
class SpriteManager;

class OutroEnding : public Scene
{
public:
	OutroEnding();
	virtual ~OutroEnding();

private:
	SpriteManager* m_pBackGround;
	ObjectManager* m_pObjectManager;

public:
	// Scene�� ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw(DesireD2D* engine2D) override;
	virtual void Release() override;
};

