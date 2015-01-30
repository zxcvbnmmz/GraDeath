#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterController.h"
#include "CharacterController/PlayerController/PlayerController.h"
#include "Object/Player.h"

#include "CharacterController/CharacterInfo.h"
#include "Loader/PlayerLoader.h"
#include "Manager/HitPointManager.h"
#include "Manager/SkillManager.h"
#include "Collision/Collision.h"

namespace PlayerManager
{
	namespace{
		const static int PLAYERS = 4;
		CharacterController* controllers[PLAYERS] = { nullptr };
		Player players[ PLAYERS ];
	}
}

bool PlayerManager::Init(PlayerData* _data){
	/*
	ここら辺でロード
	現在PlayerDataとなっているのは初期化に必要なデータ群
	どのプレイヤーがどのキャラクーを使うのかなどの情報が入っているはず
	それらのデータを使って下記の初期化を行う
	playersをコントローラー順にソートするとかやるならもここでやる
	*/
	CharacterInfo* data = ( CharacterInfo* )_data;

	for (int i = 0; i < PLAYERS; ++i){
		controllers[ i ] = new PlayerController;
		controllers[i]->Init(i,&players[i]);
		HitPointManager::Init ( i, &players[ i ], 100.0f );
		SkillManager::Init ( i, data[ i ].pType );
	}

	return true;
}

void PlayerManager::Release(){
	if (controllers == nullptr){
		return;
	}

	for (int i = 0; i < PLAYERS; ++i){
		controllers[i]->Release();
		delete controllers[ i ];
		controllers[ i ] = nullptr;
		players[i].Release();
	}
}

void PlayerManager::Update(){
	for (int i = 0; i < PLAYERS; ++i){
		controllers[i]->Update();
	}

	for (int i = 0; i < PLAYERS - 1; ++i){
		for (int k = i + 1; k < PLAYERS; ++k){
			Collision::Collide(&players[i], &players[k]);
		}
	}
}

void PlayerManager::Draw(){
    for (int i = 0; i < PLAYERS; ++i){
        controllers[i]->Draw();
    }
}

void PlayerManager::AllPlayerMove(int _movex, int _movey){
    for (int i = 0; i < PLAYERS; ++i){
        controllers[i]->Move(_movex , _movey);
    }
}
void PlayerManager::OnPlayerPos(int _Player, int _posx, int _posy){
    controllers[_Player]->SetPos(_posx, _posy);
}




