#include "Sound/BGM/BGMPimpl.h"
#include "Sound/Voice/SourceVoice.h"
#include <XAudio2.h>

namespace Sound{

BGM::BGMPimpl::BGMPimpl(std::shared_ptr<class SourceVoice> _sourceVoice, SubmixVoice* submix):sourceVoice(_sourceVoice){}

BGM::BGMPimpl::~BGMPimpl(){
	Stop();
}

bool BGM::BGMPimpl::Play(){
	(*sourceVoice)->Stop();
	if(FAILED((*sourceVoice)->Start(0,XAUDIO2_COMMIT_NOW))){
		return false;
	}
	return true;
}

void BGM::BGMPimpl::Stop(){
	(*sourceVoice)->Stop();
}

void BGM::BGMPimpl::SetVolume(float volume){
	(*sourceVoice)->SetVolume(volume);
}


void BGM::BGMPimpl::SetPitch(float pitch){
	(*sourceVoice)->SetFrequencyRatio(pitch);
}

float BGM::BGMPimpl::GetPlayingTime(){
	return sourceVoice->GetPlayingTime();
}

}