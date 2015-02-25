#include "Manager/BGMManager.h"
#include "Sound/Sound.h"

BGMManager::~BGMManager(){
}

void BGMManager::Load(char* fileName){
	BGMs.insert(std::pair<char*,BGM>(fileName, Sound::CreateBGM(fileName)));
}

void BGMManager::Play(char* fileName){
	auto it = BGMs.find(fileName);
	if (it != BGMs.end()){
		(*it).second->Play();
	}
}

void BGMManager::Stop(char* fileName){
	auto it = BGMs.find(fileName);
	if (it != BGMs.end()){
		(*it).second->Stop();
	}
}

void BGMManager::Release(){
	if (inst != nullptr){
		SafeDelete(inst);
	}
}
 