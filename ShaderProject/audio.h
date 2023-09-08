// Audioコンポーネント [audio.h]
#pragma once

#include <xaudio2.h>

class Audio
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	m_SourceVoice{};
	BYTE*					m_SoundData{};

	int						m_Length{};
	int						m_PlayLength{};

public:
	static void InitMaster();
	static void UninitMaster();

	void Uninit();

	void Load(const char *FileName);
	void Play(bool Loop = false);
};
