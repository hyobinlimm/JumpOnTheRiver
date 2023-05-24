#pragma once

#include "IScene.h"

/// <summary>
/// 모든 오브젝트와 리소스를 로드한다.
/// </summary>
class LoadingScene : public IScene
{
public:
	LoadingScene();
	~LoadingScene();

public:
	void LoadStage(int stageNumber);
};

