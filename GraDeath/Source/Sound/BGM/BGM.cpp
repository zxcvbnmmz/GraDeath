#include "Sound/BGM/BGMPimpl.h"

namespace Sound{

BGM::BGM(std::shared_ptr<class SourceVoice> _sourceVoice, SubmixVoice* submix):pimpl(new BGMPimpl(_sourceVoice)){

}

BGM::~BGM(){
	if(pimpl){
		delete pimpl;
		pimpl = nullptr;
	}
}

bool BGM::Play(){
	return pimpl->Play();
}

void BGM::Stop(){

	pimpl->Stop();
}

void BGM::SetVoume(float volume){
	pimpl->SetVolume(volume);
}

void BGM::SetPitch(float pitch){
	pimpl->SetPitch(pitch);
}

float BGM::GetPlayingTime(){
	return pimpl->GetPlayingTime();
}

}
