// ************************************************************
// filename	PlayerController.cpp
// brief	Playerの管理
// name		川口　裕
// note
// 2014.10.27
// ************************************************************

// インクルード ***********************************************
#include "CharacterController/PlayerController/PlayerController.h"
#include "Utility/SafeDelete.h"
#include "Input/GamePad.h"
#include "Object/Player.h"

void PlayerController::Init (int _padID)
{
	Release ();
	this->padID = _padID;
}

void PlayerController::Update(class Player* _player){
}

void PlayerController::Draw(class Player* _player){
}

void PlayerController::Release ()
{

}

void PlayerController::Idle(Player* _player){
	float angle;
	if (GamePad::getLStickState((PAD_NUM)padID, angle)){
		currentAction = WALK;
	}
	else if (GamePad::getGamePadState((PAD_NUM)padID, BUTTON_B) == INPUT_PUSH){
		currentAction = ATTACK;
	}
	else if (GamePad::getGamePadState((PAD_NUM)padID, BUTTON_A) == INPUT_PUSH){
		currentAction = JUMP;
	}
}

void PlayerController::Run(Player* _player){}

void PlayerController::Walk(Player* _player){}

void PlayerController::Attack(Player* _player){
	currentAction = IDLE;
}

void PlayerController::Damage(Player* _player){}

void PlayerController::Jump(Player* _player){
	currentAction = IDLE;
}






