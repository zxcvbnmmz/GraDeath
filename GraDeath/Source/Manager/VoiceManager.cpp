#include "Manager/VoiceManager.h"
#include "Sound/Sound.h"

VoiceManager::VoiceManager(){

}

VoiceManager::~VoiceManager(){
	Release();
}

void VoiceManager::Initialize(unsigned int playerID){
	for (int i = 0; i < VOICE_MAX; ++i){
		seList[i] = Sound::CreateSE(characterVoices[playerID][i]);
	}
}

void VoiceManager::Release(){
	for (int i = 0; i < VOICE_MAX; ++i){
		if(seList[i] != nullptr)
			seList[i]->Release();
	}
}

void VoiceManager::Play(VOICE_LIST voice){
	seList[voice]->Stop();
	seList[voice]->Play();
}

void VoiceManager::Stop(){

}

void VoiceManager::Pause(){
	for (int i = 0; i < VOICE_MAX; ++i){
		seList[i]->Pause();
	}
}

void VoiceManager::SetVolume(VOICE_LIST voice, float _volume){
	seList[voice]->SetVoume(_volume);
}
