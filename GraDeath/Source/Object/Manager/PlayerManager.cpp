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
	������ӂŃ��[�h
	����PlayerData�ƂȂ��Ă���̂͏������ɕK�v�ȃf�[�^�Q
	�ǂ̃v���C���[���ǂ̃L�����N�[���g���̂��Ȃǂ̏�񂪓����Ă���͂�
	�����̃f�[�^���g���ĉ��L�̏��������s��
	players���R���g���[���[���Ƀ\�[�g����Ƃ����Ȃ�������ł��
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



