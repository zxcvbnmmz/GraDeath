#ifndef _SOUND_CORE_H__
#define _SOUND_CORE_H__

struct IXAudio2;

namespace SoundCore{
	bool Initialize();
	void Release();
	IXAudio2* GetXAudio();
	class MasterVoice& GetMasteringVoice();
};

#endif	// end of SoundCore