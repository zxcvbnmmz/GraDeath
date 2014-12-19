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
#include "Manager/SkillManager.h"

#include "D2D/Text/TextObject.h"
#include "D2D/Brush/SolidBrush.h"

D2D::TextObject t;

void PlayerController::Init (int _padID, Player* _player)
{
	Release ();
	this->padID = _padID;
	this->player = _player;
	currentAction = ACTION_IDLE;
	enable = true;
	int x, y;
	System::Window::GetWindowSize ( &x, &y );
	ground = static_cast<float>(y) - 300;
	pos = D3DXVECTOR2 ( 150 + static_cast<float>( _padID )* 300.f, ground );

	animManager.Create(padID, player);
	animManager.Enable(true);

	t.format = D2D::TextFormat::Create(L"MS明朝", 20);
	t.brush = SolidBrush::Create(255, 255, 255, 255);
}

void PlayerController::Draw(){
	count = (count + 1) % 6;

	D2D1_RECT_F rect;
	animManager.GetDrawingRect(rect);
	
	b2Vec2 pos = player->GetPosition();

	D3DXVECTOR2 size = animManager.GetCellSize();
	player->sprite->SetTrimming ( rect );
	player->sprite->SetPosition ( pos.x * 32.0f, pos.y * 32.0f);
	player->sprite->SetSize ( size );
	player->sprite->Draw ( DRAW_RECT );
}

void PlayerController::Release ()
{

}

void PlayerController::Idle(){

	float angle;
	if (GamePad::getLStickState((PAD_NUM)padID, angle)){
		currentAction = ACTION_WALK;
	}
	else if ((GamePad::getGamePadState((PAD_NUM)padID, BUTTON_B) == INPUT_PUSH ||
		  Keyboard::CheckKey(KC_A) == INPUT_PUSH ) &&
		  SkillManager::GetSkillUse ( padID, (SKILL_ID)0 ) ){
		ChangeAction(ACTION_ATTACK, false);
		SkillManager::SkillOn ( padID, SKILL_ID::SKILL_FIRST, D3DXVECTOR2 ( this->player->GetPosition ().x, this->player->GetPosition ().y) );
	}
	else if (GamePad::getGamePadState((PAD_NUM)padID, BUTTON_A) == INPUT_PUSH){
		player->SetAngularVelocity(b2Vec2(0, -2000));
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

	if (Keyboard::CheckKey(KC_RIGHT) == INPUT_PRESS || Keyboard::CheckKey(KC_LEFT) == INPUT_PRESS){
		currentAction = ACTION_WALK;
	}
}

void PlayerController::Run(){}

void PlayerController::Walk(){
	if (padID != 0){
		return;
	}

	if (Keyboard::CheckKey(KC_RIGHT) == INPUT_PRESS){
		pos.x += 3.0f;
		player->AddForce(b2Vec2(10, 0));
	}

	if (Keyboard::CheckKey(KC_LEFT) == INPUT_PRESS){

		pos.x += 3.0f;
		player->AddForce(b2Vec2(-10, 0));
	}

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

void PlayerController::Attack(){
	if (currentAnimState == FINISHED){
		ChangeAction(ACTION_IDLE, true);
	}
}

void PlayerController::Damage(){}

void PlayerController::Jump(){
	ChangeAction(ACTION_IDLE, true);
}






