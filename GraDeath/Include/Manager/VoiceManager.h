#ifndef _VOICE_MANAGER_H__
#define _VOICE_MANAGER_H__

#include "Sound/SE/SE.h"
#include "Voice/VoiceList.h"

class VoiceManager{
public:
	VoiceManager();
	~VoiceManager();

	void Initialize(unsigned int playerID);
	void Play(VOICE_LIST voice);
	void Pause();
	void Stop();
	void Release();
	void SetVolume(VOICE_LIST voice, float _volume);

private:
	SE seList[VOICE_MAX];
};

#endif	// end of VoiceManager