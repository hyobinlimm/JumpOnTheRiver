#pragma once

#include "IScene.h"

/// <summary>
/// ��� ������Ʈ�� ���ҽ��� �ε��Ѵ�.
/// </summary>
class LoadingScene : public IScene
{
public:
	LoadingScene();
	~LoadingScene();

public:
	void LoadStage(int stageNumber);
};

