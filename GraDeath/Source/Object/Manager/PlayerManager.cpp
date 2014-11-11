#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterController.h"
#include "Object/Player.h"

namespace{
	const static int PLAYERS = 4;
	CharacterController* controllers[PLAYERS];
	Player players[PLAYERS];
}

bool PlayerManager::Init(PlayerData* _data){
	for (int i = 0; i < PLAYERS; ++i){
		controllers[i]->Init(0);
		players[i].Init("");
	}

	return true;
}

void PlayerManager::Update(){
	for (int i = 0; i < PLAYERS; ++i){
		controllers[i]->Update(&players[i]);
	}
}

void PlayerManager::Draw(){
	for (int i = 0; i < PLAYERS; ++i){

	}
}



