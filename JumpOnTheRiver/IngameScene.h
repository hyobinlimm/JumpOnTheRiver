#pragma once

#include "IScene.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Object.h"

class DesireD2D;
class ObjectManager;
class Object;
class SpriteManager;
class CInput;

class IngameScene : public Scene
{
public:
	IngameScene();
	virtual ~IngameScene();

private:
	SpriteManager* m_pBackGround;
	ObjectManager* m_pObjectManager;
	DesireD2D* m_pEngine2D;
public:
	CInput* m_KeyInput;

public:
	// Scene을 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
};

