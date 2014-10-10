#include "Sound/Voice/MasterVoice.h"
#include <XAudio2.h>

namespace SoundCore{

MasterVoice::MasterVoice():voice(nullptr){}

MasterVoice::~MasterVoice(){
	Release();
}

void MasterVoice::Release(){
	if(voice){
		voice->DestroyVoice();
		voice = nullptr;
	}
}

void MasterVoice::SetVolume(float volume){
	voice->SetVolume(volume);
}

}