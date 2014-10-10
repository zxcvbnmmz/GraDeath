#include "Sound/Voice/SubmixVoice.h"
#include <XAudio2.h>

namespace Sound{
SubmixVoice::SubmixVoice(IXAudio2* xaudio):voice(nullptr){
	try{
		xaudio->CreateSubmixVoice(&voice, 1, 44100);
	}
	catch (...){}
}

SubmixVoice::~SubmixVoice(){
	voice->DestroyVoice();
}

void SubmixVoice::SetVolume(float volume){
	voice->SetVolume(volume);
}

}