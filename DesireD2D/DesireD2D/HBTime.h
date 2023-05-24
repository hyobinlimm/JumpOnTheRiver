#pragma once
#include "TamplateSingleton.h"

/// <summary>
/// 게임의 시간을 관리
/// 
/// 시작 과 끝
/// 
/// 22. 02. 10
/// </summary>

class HBTime : public TemplateSingleton<HBTime>
{
public:
	HBTime();
	~HBTime();

private:
	LARGE_INTEGER m_BeginTime;
	LARGE_INTEGER m_Frequency;
	LARGE_INTEGER m_CurrentTime;
	double m_DeltaCount;
	double m_DeltaTime;
	double m_SecondsPerCount;

	double m_FPS;
	double m_TimeSeconde; 

	static HBTime* m_pInstance;

public:
	
	void Initialize();

	double GetFPS();

	void GetBeginTime();
	void GetEndTime();
	float GetDeltaTime();
	
	void Update();

	void UpdateFPS();

	LARGE_INTEGER GetBeginTime() const { return m_BeginTime; }
	LARGE_INTEGER GetEndtime() const { return m_CurrentTime; }
};

