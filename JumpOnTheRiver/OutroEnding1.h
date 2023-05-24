#pragma once

#include "IScene.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Object.h"
#include "ObjectManager.h"

class ObjectManager;
class Object;
class SpriteManager;

class OutroEnding1 : public Scene
{
public:
	OutroEnding1();
	virtual ~OutroEnding1();

private:

public:
	// Scene을 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
};

