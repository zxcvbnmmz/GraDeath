#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterController.h"
#include "CharacterController/PlayerController/PlayerController.h"
#include "Object/Player.h"

#include "CharacterController/CharacterInfo.h"
#include "Loader/PlayerLoader.h"

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
	������ӂŃ��[�h
	����PlayerData�ƂȂ��Ă���̂͏������ɕK�v�ȃf�[�^�Q
	�ǂ̃v���C���[���ǂ̃L�����N�[���g���̂��Ȃǂ̏�񂪓����Ă���͂�
	�����̃f�[�^���g���ĉ��L�̏��������s��
	players���R���g���[���[���Ƀ\�[�g����Ƃ����Ȃ�������ł��
	*/
	CharacterInfo* data = ( CharacterInfo* )_data;

	for (int i = 0; i < PLAYERS; ++i){
		controllers[ i ] = new PlayerController;
		controllers[i]->Init(i);
		players[ i ].Init ( "test" );
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
		controllers[i]->Update(&players[i]);
	}
}

void PlayerManager::Draw(){
	for (int i = 0; i < PLAYERS; ++i){
		controllers[i]->Draw(&players[i]);
	}
}



