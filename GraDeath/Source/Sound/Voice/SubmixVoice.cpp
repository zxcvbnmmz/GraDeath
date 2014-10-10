#include "Sound/Voice/SubmixVoice.h"
#include <XAudio2.h>

namespace Sound{
SubmixVoice::SubmixVoice(IXAudio2* xaudio):voice(nullptr){
	xaudio->CreateSubmixVoice(&voice,1,44100);
}

SubmixVoice::~SubmixVoice(){
	voice->DestroyVoice();
}

void SubmixVoice::SetVolume(float volume){
	voice->SetVolume(volume);
}

}