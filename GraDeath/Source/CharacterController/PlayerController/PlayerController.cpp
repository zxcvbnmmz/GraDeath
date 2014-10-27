// ************************************************************
// filename	PlayerController.cpp
// brief	Player�̊Ǘ�
// name		����@�T
// note
// 2014.10.27
// ************************************************************

// �C���N���[�h ***********************************************
#include "Object/Character.h"
#include "CharacterController/PlayerController/PlayerController.h"
#include "Utility/SafeDelete.h"


void PlayerController::Init ()
{
	Release ();
	player.resize ( PLAYER_NUM );
	for ( auto& _player : player )
		_player = nullptr;
}

void PlayerController::Update ()
{
	for ( int i = 0; i < PLAYER_NUM; i++ )
	{
		//if ( player[ i ] == nullptr )
		//	player[ i ]->Update ();
	}
}

void PlayerController::Draw ()
{
	for ( int i = 0; i < PLAYER_NUM; i++ )
	{
		//if ( player[ i ] == nullptr )
		//	player[ i ]->Draw ();
	}
}

void PlayerController::Release ()
{
	if ( !player.empty () )
	{
		for ( auto& _player : player )
			Util::safeDelete ( _player );
		player.clear ();
	}
}

void PlayerController::SetCharacter ( Character* _character, int _num )
{
	player[ _num ] = _character;
}

PlayerController* PlayerController::Create ()
{
	return new PlayerController;
}