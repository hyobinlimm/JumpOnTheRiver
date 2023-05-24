#include "pch.h"
#include "HBTime.h"

HBTime* HBTime::m_pInstance = nullptr;

HBTime::HBTime()
	:m_DeltaCount(0),m_DeltaTime(0), m_SecondsPerCount(0), m_FPS(0), m_TimeSeconde(0)
{
	// 생성이 될 때 시간을 처음 시간을 받아온다. 
	this->Initialize();
}

HBTime::~HBTime()
{
	DestroyInstance();
}

void HBTime::Initialize()
{
	// 프로그램이나 클래스 시작부분
	// 자기 시스템이 최대 어느 정도까지의 timer resolution를 지원하는지 판별하는데 사용
	// 초당 진동수 반환. 
	QueryPerformanceFrequency(&m_Frequency);

	// 1카운트당 몇 초나 걸리는 지 알려줌. 
	// LowPart는 DWORD
	// QuadPart는 unsinged int (64비트 정수)라고 한다. 
	m_SecondsPerCount = 1.0 / (double)m_Frequency.QuadPart;

	m_FPS = 60.f;
	m_TimeSeconde = 1.0f / m_FPS; // 0.016
}

double HBTime::GetFPS()
{
	if (m_DeltaTime != 0)
	{
		return (double)(1.0 / m_DeltaTime);
	}

	return 0;
}

void HBTime::GetBeginTime()
{
	// 현재 카운터를 알아내는데 사용
	QueryPerformanceCounter(&m_BeginTime);
}

void HBTime::GetEndTime()
{
	QueryPerformanceCounter(&m_CurrentTime);
}

float HBTime::GetDeltaTime()
{
	//m_DeltaTime = m_DeltaCount / m_Frequency.QuadPart;

	// why? 어째서? 이유를 모르겠음. 
	return (float)m_DeltaTime;
}

void HBTime::Update()
{
	QueryPerformanceCounter(&m_CurrentTime);

	// 시작 후 update기 까지 걸린 count를 잰다. 
	m_DeltaCount = m_CurrentTime.QuadPart - m_BeginTime.QuadPart;

	// 계산 된 count를 초로 바꿔준다. 
	m_DeltaTime = m_DeltaCount / m_Frequency.QuadPart;

	// 시작초에 현재 초를 넣어준다. 
	// why? 지금은 currentTime이 과거가 되고 update가 다시 불렸을때 잰 current가 현재 시간이 된다. 
	m_BeginTime = m_CurrentTime;

	m_SecondsPerCount = m_DeltaCount / (double)m_Frequency.QuadPart;
	//m_SecondsPerCount *= 1000;

	if (m_DeltaCount < 0)
	{
		m_DeltaCount = 0;
	}

}

void HBTime::UpdateFPS()
{
	QueryPerformanceCounter(&m_CurrentTime); //현재 시간

	static double _FlowTime = 0; 
	static DWORD FrameCount = 0; // 프레임 카운트 수 
	
	// 현재 진동수에서 과거의 진동수를 뺀다. 
	m_DeltaCount = m_CurrentTime.QuadPart - m_BeginTime.QuadPart;

	// 1. delta time(한 프레임에 몇초가 지났는지)를 구한다. 
	m_DeltaTime = m_DeltaCount / m_Frequency.QuadPart;

	// m_DeltaTime는 ms이기 때문에 천으로 나눈다. 
	_FlowTime += (m_DeltaTime / 1000);

	FrameCount++;

	//1초에 60번을 돌았으면 그만 그리라는 의미
	if ( 1.0f < m_DeltaTime )         //흐른시간이 1초이상이면 내가 하고싶은것 처리
	{
		FrameCount = 0;
		_FlowTime = 0.0f;
	}

	m_BeginTime = m_CurrentTime;
	


	// 2. 다음 번쨰 delta time과 과거의 delta time의 차이에서 몇초가 지났는지 알 수 있음. 

	// 3. daltatime들을 누적해서 1초가 되었으면 0으로 초기화 

	// 4. 1초 동안 프레임을 몇번 그렸는지 알아야 한다. 
}

