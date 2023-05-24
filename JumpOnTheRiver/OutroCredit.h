#pragma once

#include "IScene.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Object.h"
#include "ObjectManager.h"

class ObjectManager;
class Object;
class SpriteManager;

class OutroCredit: public Scene
{
public:
	OutroCredit();
	virtual ~OutroCredit();

private:

public:
	// Scene을 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
};

