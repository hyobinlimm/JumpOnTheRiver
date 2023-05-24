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

class IntroCutScene2 : public Scene
{
public:
	IntroCutScene2();
	virtual ~IntroCutScene2();

private:
	SmartInput m_SmartKeyInput;

public:
	// Scene�� ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
};

