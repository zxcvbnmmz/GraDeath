#include "Sound/SE/SEPimpl.h"

namespace Sound{

SE::SE(std::shared_ptr<class SourceVoice> _sourceVoice, SubmixVoice* submix):pimpl(new SEPimpl(_sourceVoice)){}

SE::~SE(){
	if(pimpl){
		delete pimpl;
		pimpl = nullptr;
	}
}

bool SE::Play(bool cueing){
	return pimpl->Play(cueing);
}

void SE::Pause(){
	pimpl->Pause();
}

void SE::Stop(){
	pimpl->Stop();
}

void SE::SetVoume(float volume){
	pimpl->SetVolume(volume);
}

void SE::SetPitch(float pitch){
	pimpl->SetPitch(pitch);
}

float SE::GetPlayingTime(){
	return pimpl->GetPlayingTime();
}

}
