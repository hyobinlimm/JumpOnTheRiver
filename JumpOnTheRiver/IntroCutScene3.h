#pragma once

#include "IScene.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Object.h"
#include "ObjectManager.h"
#include "SmartInput.h"

class ObjectManager;
class Object;
class SpriteManager;

class IntroCutScene3 : public Scene
{
public:
	IntroCutScene3();
	virtual ~IntroCutScene3();

private:
	SmartInput m_SmartKeyInput;

public:
	// Scene을 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
};

