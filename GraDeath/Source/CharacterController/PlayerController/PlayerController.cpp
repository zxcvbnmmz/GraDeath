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

void PlayerController::Init (int _padID, Player* _player, float scale)
{
    
	Release ();
	this->padID = _padID;
	this->player = _player;
	currentAction = ACTION_IDLE;
	enable = true;
	int x, y;
	System::Window::GetWindowSize ( &x, &y );
	ground = static_cast<float>(y) - 300;

	animManager.Create ( _padID, player, scale );
	animManager.Enable(true);

	voiceManager.Initialize(player->playerType);

#ifdef _DEBUG
	t.format = D2D::TextFormat::Create(L"MS明朝", 20);
	t.brush = SolidBrush::Create(255, 255, 255, 255);
#endif
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
	PLAYER_DIRECTION dir = animManager.GetCurrentDirecton();
	player->sprite->SetReverseFlag(dir == RIGHT ? FLIP_NONE : FLIP_HORIZONTAL);
	player->sprite->Draw ( DRAW_RECT );

	//if(padID == 0)
	//	t.DrawString(0, 0, L"LinearVelocity  x = %f, y = %f", player->body->GetLinearVelocity().x, player->body->GetLinearVelocity().y);
}

void PlayerController::Release ()
{
}

void PlayerController::SetDamage ()
{
	if ( currentAction != ACTION_DAMAGE )
		ChangeAction ( ACTION_DAMAGE, false, SAME_BEFORE );
}

void PlayerController::Idle(){

	float angle;
	if (GamePad::getLStickState((PAD_NUM)padID, angle)){
		ChangeAction(ACTION_WALK, true, SAME_BEFORE);
	}
	else if ( GamePad::getGamePadState((PAD_NUM)padID, BUTTON_B) == INPUT_PUSH
		&& SkillManager::GetSkillUse ( padID, (SKILL_ID)0 ) ){
		bool temp = SkillManager::SkillOn ( padID, SKILL_ID::SKILL_FIRST, D3DXVECTOR2 ( this->player->GetPosition ().x, this->player->GetPosition ().y ), animManager.GetCurrentDirecton () );
		if ( temp )
			ChangeAction(ACTION_SKILL, false);	
	}
	else if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_Y ) == INPUT_PUSH
		&& SkillManager::GetSkillUse ( padID, ( SKILL_ID )1 ) ){
		bool temp = SkillManager::SkillOn ( padID, SKILL_ID::SKILL_SECOND, D3DXVECTOR2 ( this->player->GetPosition ().x, this->player->GetPosition ().y ), animManager.GetCurrentDirecton () );
		if ( temp )
	 		ChangeAction ( ACTION_SKILL_2, false );
	}
	else if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_X ) == INPUT_PUSH
#ifdef _DEBUG
		|| ( Keyboard::CheckKey ( KC_D ) == INPUT_PUSH && ( padID == 0 ) )
#endif
		&& SkillManager::GetSkillUse ( padID, ( SKILL_ID )2 ) ){
		bool temp = SkillManager::SkillOn ( padID, SKILL_ID::SKILL_THIRD, D3DXVECTOR2 ( this->player->GetPosition ().x, this->player->GetPosition ().y ), animManager.GetCurrentDirecton () );
		if ( temp )
			ChangeAction ( ACTION_SKILL_3, false );		
	}
	else if (GamePad::getGamePadState((PAD_NUM)padID, BUTTON_A) == INPUT_PUSH
#ifdef _DEBUG
		|| ( Keyboard::CheckKey ( KC_J ) == INPUT_PUSH && ( padID == 0 ) )
#endif
		){
		player->SetAngularVelocity(b2Vec2(0, -2000));
		ChangeAction(ACTION_JUMP_RISE, false, SAME_BEFORE);
	}
	else if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_RIGTH ) == INPUT_PRESS ){
		ChangeAction(ACTION_WALK, true, RIGHT);
	}
	else if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_LEFT ) == INPUT_PRESS ){
		ChangeAction(ACTION_WALK, true, LEFT);
	}

#ifdef _DEBUG
	if ( ( padID  == 0 ) && ( Keyboard::CheckKey ( KC_RIGHT ) == INPUT_PRESS || Keyboard::CheckKey ( KC_LEFT ) == INPUT_PRESS ) ){
		ChangeAction(ACTION_WALK, true,SAME_BEFORE);
	}
#endif
}

void PlayerController::Run(){}

void PlayerController::MovePos(int _movex,int _movey){
    b2Vec2 pos = player->GetPosition();
    player->AddForce(b2Vec2(_movex, _movey));
}

void PlayerController::SetPos(int posx, int posy, float angle){
	player->body->SetTransform(b2Vec2(posx, posy), angle);
}

void PlayerController::Walk(){
	if (padID != 0){
//		return;
	}

	if (player->body->GetLinearVelocity().y < -0.3){
		ChangeAction(ACTION_JUMP_FALL, true, SAME_BEFORE);
		return;
	}

	if (Keyboard::CheckKey(KC_RIGHT) == INPUT_PRESS){
		player->AddForce(b2Vec2(10, 0));
		return;
	}else if (Keyboard::CheckKey(KC_LEFT) == INPUT_PRESS){
		player->AddForce(b2Vec2(-10, 0));
		return;
	}
	
	Move();
	if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_RIGTH ) != INPUT_PRESS &&
		GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_LEFT ) != INPUT_PRESS ){
		ChangeAction(ACTION_IDLE, true, SAME_BEFORE);
	}

	if ( GamePad::getGamePadState ( ( PAD_NUM )padID, BUTTON_A ) == INPUT_PUSH ){
		player->SetAngularVelocity(b2Vec2(0, -2000));
		ChangeAction(ACTION_JUMP_RISE, false, SAME_BEFORE);
	}
}

void PlayerController::Damage(){
	if ( currentAnimState == FINISHED ){
		ChangeAction ( ACTION_IDLE, false, SAME_BEFORE );
	}
}

void PlayerController::Jump_Rise(){
	Move();
	if (player->body->GetLinearVelocity().y >= 0){
		ChangeAction(ACTION_JUMP_FALL, false, SAME_BEFORE);
	}
}

void PlayerController::Jump_Fall(){
	Move();
	if (player->body->GetLinearVelocity().y <= 0){
		ChangeAction(ACTION_JUMP_LAND, false, SAME_BEFORE);
	}
}

void PlayerController::Jump_Land(){
	if (currentAnimState == FINISHED){
		float angle;
		if (GamePad::getLStickState((PAD_NUM)padID, angle)){
			ChangeAction(ACTION_WALK, true, SAME_BEFORE);
		}
		ChangeAction(ACTION_IDLE, true, SAME_BEFORE);
	}
}


void PlayerController::Skill(){
	if (currentAnimState == FINISHED){
		ChangeAction(ACTION_IDLE, false, SAME_BEFORE);
	}
}


void PlayerController::Move(){
	if (GamePad::getGamePadState((PAD_NUM)padID, BUTTON_RIGTH) == INPUT_PRESS){
		player->AddPosition(4.0f / 32.0f, 0);
	}
	else if (GamePad::getGamePadState((PAD_NUM)padID, BUTTON_LEFT) == INPUT_PRESS){
		player->AddPosition(-4.0f / 32.0f, 0);
	}
}
