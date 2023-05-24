#pragma once

#include "IScene.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Object.h"
#include "ObjectManager.h"

class ObjectManager;
class Object;
class SpriteManager;

class OutroEnding2 : public Scene
{
public:
	OutroEnding2();
	virtual ~OutroEnding2();

private:

public:
	// Scene�� ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
};

