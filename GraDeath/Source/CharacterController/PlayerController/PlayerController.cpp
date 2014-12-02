// ************************************************************
// filename	PlayerController.cpp
// brief	Playerの管理
// name		川口　裕
// note
// 2014.10.27
// ************************************************************

// インクルード ***********************************************
#include "D2D/Sprite/Sprite.h"
#include "CharacterController/PlayerController/PlayerController.h"
#include "Object/ObjectParameter.h"
#include "Input/GamePad.h"
#include "Object/Player.h"
#include "Input/GamePad.h"
#include "System/Window.h"
#include "Input/Keyboard.h"

void PlayerController::Init (int _padID)
{
	Release ();
	this->padID = _padID;
	currentAction = ACTION_IDLE;
	enable = true;
	int x, y;
	System::Window::GetWindowSize ( &x, &y );
	ground = static_cast<float>(y) - 300;
	pos = D3DXVECTOR2 ( 150 + static_cast<float>( _padID )* 300.f, ground );

	animManager.Create(padID);
	animManager.Enable(true);
}

void PlayerController::Draw(class Player* _player){
	count = (count + 1) % 6;

	D2D1_RECT_F rect;
	animManager.GetDrawingRect(rect);


	D3DXVECTOR2 size = _player->animData.cellSize;
	_player->sprite->SetTrimming ( rect );
	_player->sprite->SetPosition ( pos );
	_player->sprite->SetSize ( size );
	_player->sprite->Draw ( DRAW_RECT );
}

void PlayerController::Release ()
{

}

void PlayerController::Idle(Player* _player){

	float angle;
	if (GamePad::getLStickState((PAD_NUM)padID, angle)){
		currentAction = ACTION_WALK;
	}
	else if (GamePad::getGamePadState((PAD_NUM)padID, BUTTON_B) == INPUT_PUSH ||
		  Keyboard::CheckKey(KC_A) == INPUT_PUSH){
		ChangeAction(ACTION_ATTACK, false);
	}
	else if (GamePad::getGamePadState((PAD_NUM)padID, BUTTON_A) == INPUT_PUSH){
		currentAction = ACTION_JUMP;
	}
	else if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_RIGTH ) == INPUT_PRESS ){
		currentAction = ACTION_WALK;
	}
	else if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_LEFT ) == INPUT_PRESS ){
		currentAction = ACTION_WALK;
	}
	//count = ( count + 1 ) % 6;
	//std::vector< std::shared_ptr< CellData > > cellData = _player->animData.cellDatas[ 0 ];
	//cellData[ 0 ]->animFrame;
}

void PlayerController::Run(Player* _player){}

void PlayerController::Walk(Player* _player){
	if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_RIGTH ) == INPUT_PRESS ){
		pos.x += 4.0f;
	}
	else if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_LEFT ) == INPUT_PRESS ){
		pos.x -= 4.0f;
	}
	else{
		currentAction = ACTION_IDLE;
	}

	if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_A ) == INPUT_PUSH ){
		currentAction = ACTION_JUMP;
	}
}

void PlayerController::Attack(Player* _player){
	if (currentAnimState == FINISHED){
		ChangeAction(ACTION_IDLE, true);
	}
}

void PlayerController::Damage(Player* _player){}

void PlayerController::Jump(Player* _player){

	static float jumpCount = -20.0f;
	jumpCount += 0.98f;
	pos.y += jumpCount;
	if ( pos.y > ground )
	{
		pos.y = ground;
		currentAction = ACTION_IDLE;
		jumpCount = -20.0f;
	}
	if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_RIGTH ) == INPUT_PRESS ){
		pos.x += 4.0f;
	}
	else if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_LEFT ) == INPUT_PRESS ){
		pos.x -= 4.0f;
	}
}






