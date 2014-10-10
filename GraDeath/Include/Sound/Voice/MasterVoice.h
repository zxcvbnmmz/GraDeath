#ifndef _MASTER_VOICE_H__
#define _MASTER_VOICE_H__

struct IXAudio2MasteringVoice;

namespace SoundCore{
struct Core;

class MasterVoice{
public:
	IXAudio2MasteringVoice* operator->(){return voice;}
	IXAudio2MasteringVoice* operator->()const{return voice;}
	IXAudio2MasteringVoice** operator&(){return &voice;}
	void Release();
	void SetVolume(float volume);
	
private:
friend struct Core;
	MasterVoice();
	MasterVoice(const MasterVoice&);
	MasterVoice& operator=(const MasterVoice&);
	~MasterVoice();

	IXAudio2MasteringVoice* voice;
	
};

}

#endif	// end of MasterVoice