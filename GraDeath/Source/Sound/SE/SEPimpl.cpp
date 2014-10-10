#include "Sound/SE/SEPimpl.h"
#include "Sound/Voice/SourceVoice.h"
#include <XAudio2.h>

namespace Sound{

SE::SEPimpl::SEPimpl(std::shared_ptr<class SourceVoice> _sourceVoice, SubmixVoice* submix):sourceVoice(_sourceVoice){}

SE::SEPimpl::~SEPimpl(){
	Stop();
}

bool SE::SEPimpl::Play(bool cueing){
	if(cueing){
		Stop();
	}

	if(FAILED((*sourceVoice)->Start(0,XAUDIO2_COMMIT_NOW))){
		return false;
	}
	return true;
}

void SE::SEPimpl::Stop(){
	(*sourceVoice)->Stop();
	sourceVoice->SubmitBuffer();
}

void SE::SEPimpl::Pause(){
	(*sourceVoice)->Stop();
}

void SE::SEPimpl::SetVolume(float volume){
	(*sourceVoice)->SetVolume(volume);
}

void SE::SEPimpl::SetPitch(float pitch){
	(*sourceVoice)->SetFrequencyRatio(pitch);
}

float SE::SEPimpl::GetPlayingTime(){
	return sourceVoice->GetPlayingTime();
}

}