#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterController.h"
#include "CharacterController/PlayerController/PlayerController.h"
#include "Object/Player.h"

#include "CharacterController/CharacterInfo.h"
#include "Loader/PlayerLoader.h"
#include "Manager/HitPointManager.h"

#include "World/World.h"

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

	int c = World::GetContactCount();
	b2Contact* contacts = World::GetContactList();
	for (int i = 0; i < c; ++i){
		b2Body* bodyA = contacts->GetFixtureA()->GetBody();
		b2Body* bodyB = contacts->GetFixtureB()->GetBody();

		b2Fixture* fixA = contacts->GetFixtureA();
		b2Fixture* fixB = contacts->GetFixtureB();
		contacts = contacts->GetNext();
		int a = 0;
	}

}

void PlayerManager::Draw(){
	for (int i = 0; i < PLAYERS; ++i){
		controllers[i]->Draw();
	}
}



