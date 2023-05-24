#include "pch.h"
#include "HBTime.h"

HBTime* HBTime::m_pInstance = nullptr;

HBTime::HBTime()
	:m_DeltaCount(0),m_DeltaTime(0), m_SecondsPerCount(0), m_FPS(0), m_TimeSeconde(0)
{
	// ������ �� �� �ð��� ó�� �ð��� �޾ƿ´�. 
	this->Initialize();
}

HBTime::~HBTime()
{
	DestroyInstance();
}

void HBTime::Initialize()
{
	// ���α׷��̳� Ŭ���� ���ۺκ�
	// �ڱ� �ý����� �ִ� ��� ���������� timer resolution�� �����ϴ��� �Ǻ��ϴµ� ���
	// �ʴ� ������ ��ȯ. 
	QueryPerformanceFrequency(&m_Frequency);

	// 1ī��Ʈ�� �� �ʳ� �ɸ��� �� �˷���. 
	// LowPart�� DWORD
	// QuadPart�� unsinged int (64��Ʈ ����)��� �Ѵ�. 
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
	// ���� ī���͸� �˾Ƴ��µ� ���
	QueryPerformanceCounter(&m_BeginTime);
}

void HBTime::GetEndTime()
{
	QueryPerformanceCounter(&m_CurrentTime);
}

float HBTime::GetDeltaTime()
{
	//m_DeltaTime = m_DeltaCount / m_Frequency.QuadPart;

	// why? ��°��? ������ �𸣰���. 
	return (float)m_DeltaTime;
}

void HBTime::Update()
{
	QueryPerformanceCounter(&m_CurrentTime);

	// ���� �� update�� ���� �ɸ� count�� ���. 
	m_DeltaCount = m_CurrentTime.QuadPart - m_BeginTime.QuadPart;

	// ��� �� count�� �ʷ� �ٲ��ش�. 
	m_DeltaTime = m_DeltaCount / m_Frequency.QuadPart;

	// �����ʿ� ���� �ʸ� �־��ش�. 
	// why? ������ currentTime�� ���Ű� �ǰ� update�� �ٽ� �ҷ����� �� current�� ���� �ð��� �ȴ�. 
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
	QueryPerformanceCounter(&m_CurrentTime); //���� �ð�

	static double _FlowTime = 0; 
	static DWORD FrameCount = 0; // ������ ī��Ʈ �� 
	
	// ���� ���������� ������ �������� ����. 
	m_DeltaCount = m_CurrentTime.QuadPart - m_BeginTime.QuadPart;

	// 1. delta time(�� �����ӿ� ���ʰ� ��������)�� ���Ѵ�. 
	m_DeltaTime = m_DeltaCount / m_Frequency.QuadPart;

	// m_DeltaTime�� ms�̱� ������ õ���� ������. 
	_FlowTime += (m_DeltaTime / 1000);

	FrameCount++;

	//1�ʿ� 60���� �������� �׸� �׸���� �ǹ�
	if ( 1.0f < m_DeltaTime )         //�帥�ð��� 1���̻��̸� ���� �ϰ������ ó��
	{
		FrameCount = 0;
		_FlowTime = 0.0f;
	}

	m_BeginTime = m_CurrentTime;
	


	// 2. ���� ���� delta time�� ������ delta time�� ���̿��� ���ʰ� �������� �� �� ����. 

	// 3. daltatime���� �����ؼ� 1�ʰ� �Ǿ����� 0���� �ʱ�ȭ 

	// 4. 1�� ���� �������� ��� �׷ȴ��� �˾ƾ� �Ѵ�. 
}

