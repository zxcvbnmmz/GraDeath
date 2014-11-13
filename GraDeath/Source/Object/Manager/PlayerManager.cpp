#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterController.h"
#include "Object/Player.h"

namespace{
	const static int PLAYERS = 4;
	CharacterController* controllers[PLAYERS];
	Player players[PLAYERS];
}

bool PlayerManager::Init(PlayerData* _data){
	/*
	ここら辺でロード
	現在PlayerDataとなっているのは初期化に必要なデータ群
	どのプレイヤーがどのキャラクーを使うのかなどの情報が入っているはず
	それらのデータを使って下記の初期化を行う
	playersをコントローラー順にソートするとかやるならもここでやる
	*/

	for (int i = 0; i < PLAYERS; ++i){
		controllers[i]->Init(i);
		players[i].Init("");
	}

	return true;
}

void PlayerManager::Release(){
	for (int i = 0; i < PLAYERS; ++i){
		controllers[i]->Release();
		players[i].Release();
	}
}

void PlayerManager::Update(){
	for (int i = 0; i < PLAYERS; ++i){
		controllers[i]->Update(&players[i]);
	}
}

void PlayerManager::Draw(){
	for (int i = 0; i < PLAYERS; ++i){
		controllers[i]->Draw(&players[i]);
	}
}



