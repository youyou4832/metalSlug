#pragma once
#include "singletonBase.h"

// fmod 관련 파일
#include "inc/fmod.hpp"

#pragma comment(lib, "lib/fmodex_vc.lib")

#define EXTRA_CHANNEL_BUFFER	5
#define SOUND_BUFFER			10
#define TOTAL_SOUND_BUFFER		EXTRA_CHANNEL_BUFFER + SOUND_BUFFER

using namespace FMOD;

class soundManager : public singletonBase<soundManager>
{
private:
	System*	m_system;
	Sound**	m_sound;
	Channel** m_channel;

	map<string, Sound**> m_mapSounds;
	/*map<string, Sound**>::iterator m_iterSound;

	map<string, Channel**> m_mapChannels;
	map<string, Channel**>::iterator m_iterChannel;*/
public:
	HRESULT init();
	void release();
	void update();

	void addSound(string soundName, bool isBGM, bool isLoop);
	void play(string soundName, float volume = 1.0f); // min 0.0f, max 1.0f
	void stop(string soundName);
	void pause(string soundName);
	void resume(string soundName);

	bool isPlaying(string soundName);
	bool isPause(string soundName);

	soundManager();
	~soundManager();
};

