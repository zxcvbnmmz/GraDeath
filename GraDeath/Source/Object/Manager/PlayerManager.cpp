#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterController.h"
#include "Object/Player.h"

#include "CharacterController/CharacterInfo.h"
#include "Loader/PlayerLoader.h"

namespace{
	const static int PLAYERS = 4;
	CharacterController* controllers[PLAYERS];
	Player players[PLAYERS];
}

bool PlayerManager::Init(PlayerData* _data){
	CharacterInfo* data = ( CharacterInfo* )_data;
	for (int i = 0; i < PLAYERS; ++i){
		data[ i ];
		//controllers[i]->Init(0);
		players[ i ].Init ( PlayerLoader::GetLoadFileName ( data[i].pType ) );
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



