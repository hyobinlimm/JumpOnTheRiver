#pragma once

#include "IScene.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Object.h"
#include "SmartInput.h"

class ObjectManager;
class Object;

class TitleScene : public Scene
{
public:
	TitleScene();
	virtual ~TitleScene();

private:
	SmartInput m_SmartKeyInput;

public:
	// Scene을 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
};

