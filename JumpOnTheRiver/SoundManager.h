#pragma once


#include "framework.h"
#include "Define.h"

#include "fmod.h"
#pragma comment(lib, "fmod_vc.lib")
#pragma comment(lib, "fmodL_vc.lib")

#include <map>
#include <vector>
#include <math.h>
#include <list>
#include <string>


enum class SoundInfo
{
	None,
	Loop,
};

class Channel
{
public:
	Channel() : FmodChannel(nullptr), Volume(SOUND_DEFAULT), IsPlaying(false) {};;
	~Channel() {};

	FMOD_CHANNEL* FmodChannel;
	float Volume;
	FMOD_BOOL IsPlaying;
};

/// <summary>
/// 사운드를 로드하고 관리하는 사운드 매니저
/// 2022. 02. 09 Son
/// </summary>
class SoundManager
{
private:
	static SoundManager* m_Instance;
public:
	static SoundManager* GetInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new SoundManager();
		}
		return m_Instance;
	}

private:
	SoundManager();
	~SoundManager();
	static FMOD_SYSTEM* FmodSoundSystem;

private:
	std::map<CString, FMOD_SOUND*> m_SoundFileMap;		// 사운드
	std::vector<Channel*> m_ChannelVec;
	int m_ChannelCount;

public:
	void Initialize(int channelCount);
	void Release();

	void LoadSoundFile(CString folderPath);
	void CreateSound(PCSTR path, PCWSTR soundName, SoundInfo info);
	void CreateChannel();

	void Play(unsigned int channelNum, CString soundName);
	void Pause(int channelNum, CString soundName);
	void Resume(int channelNum, CString soundName);
	void Stop(int channelNum, CString soundName);
	void VolumeUp(signed int channelNum);
	void VolumeDown(int channelNum);
	void Update();
	static std::string CStrToStr(CString Cstr);
	static std::wstring CStrToWStr(CString Cstr);
public:
	static void DeleteInstance()
	{
		if (m_Instance != nullptr)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
};

