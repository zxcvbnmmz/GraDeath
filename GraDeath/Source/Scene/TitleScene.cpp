#include "Scene/TitleScene.h"
#include "Graphic/Camera/Camera.h"
#include "System/Window.h"

#include "Scene/Factory/CharacterSelectFactory.h"
#include "Scene/Factory/CaptureFactory.h"
#include "Scene/Factory/CreditFactory.h"
#include "Input/Gamepad.h"

#include "Input\Keyboard.h"
#include "Utility/Delegate.h"
#include "Utility/ScreenShot.h"

TitleScene::TitleScene(){
	sStart.Create(L"Resource/Texture/Start.png");
	sCredit.Create(L"Resource/Texture/Credit.png");
	sExit.Create(L"Resource/Texture/Exit.png");
	sVector.Create(L"Resource/Texture/Vector.png");

	start_pos = D3DXVECTOR2(700, 200);
	credit_pos = D3DXVECTOR2(800, 400);
	exit_pos = D3DXVECTOR2(800, 600);
	vect_pos = D3DXVECTOR2(600, 200);
	vect_move =
		start_move =
		credit_move =
		exit_move = D3DXVECTOR2(0, 0);
	tCount = 0;
	select_i = 0;

	AddFunction(this, &TitleScene::ExecuteSelect);
	AddFunction(this, &TitleScene::ExecuteFadeOut);
	AddFunction(this, &TitleScene::DrawSelect);
	AddFunction(this, &TitleScene::DrawFadeOut);
	currentState = SELECT;
	fade.SetAlpha(0);
	timer.Set(60);
}

TitleScene::~TitleScene(){

}

SCENE_STATUS TitleScene::Execute(){
	int status = (int)(*executes[currentState])();
	//return STILL_PROCESSING;
	if (Keyboard::CheckKey(KC_P) == INPUT_STATE::INPUT_PUSH){
		CaptureFactory cf;
		SceneFactory::Reserve(&cf);
		return END_PROCESS;
	}

	return (SCENE_STATUS)status;
}

void TitleScene::Draw(){
	(*draws[currentState])();
}

void TitleScene::DrawSelect(){
	sVector.SetPosition(vect_pos + vect_move);
	switch (select_i){
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	}
	sStart.SetPosition(start_pos + start_move);
	sCredit.SetPosition(credit_pos + credit_move);
	sExit.SetPosition(exit_pos + exit_move);
	sStart.Draw();
	sCredit.Draw();
	sExit.Draw();
	sVector.SetPositionY(vect_pos.y + select_i * 200 + vect_move.y);
	sVector.Draw();
}

void TitleScene::DrawFadeOut(){
	DrawSelect();
	fade.Draw();
}

void TitleScene::Move() {

	if (select_i < 0) {
		select_i = 2;
		vect_move = D3DXVECTOR2(0, -400);
	}
	else if (select_i >= 3)
	{
		select_i = 0;
		vect_move = D3DXVECTOR2(0, 400);
	}

	switch (select_i){
	case 0:
		start_move.x += 100;
		if (credit_pos.x == 700)credit_move.x -= 100;
		if (exit_pos.x == 700)exit_move.x -= 100;
		start_pos.x = 700;
		credit_pos.x = 800;
		exit_pos.x = 800;
		break;
	case 1:
		credit_move.x += 100;
		if (start_pos.x == 700)start_move.x -= 100;
		if (exit_pos.x == 700)exit_move.x -= 100;
		start_pos.x = 800;
		credit_pos.x = 700;
		exit_pos.x = 800;
		break;
	case 2:
		exit_move.x += 100;
		if (start_pos.x == 700)start_move.x -= 100;
		if (credit_pos.x == 700)credit_move.x -= 100;
		start_pos.x = 800;
		credit_pos.x = 800;
		exit_pos.x = 700;
		break;
	}
}

int TitleScene::ExecuteSelect(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_A, 0) == INPUT_PUSH ||
#ifdef _DEBUG
		Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH){
#endif
		switch (select_i){
		case 0:
		case 1:
			currentState = FADE_OUT;
		}
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_DOWN, 0) == INPUT_PUSH ||
#ifdef _DEBUG
		Keyboard::CheckKey(KC_DOWN) == INPUT_PUSH) {
#endif
		select_i++;
		vect_move += D3DXVECTOR2(0, -200);
		Move();
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_UP, 0) == INPUT_PUSH ||
#ifdef _DEBUG
		Keyboard::CheckKey(KC_UP) == INPUT_PUSH) {
#endif
		select_i--;
		vect_move += D3DXVECTOR2(0, 200);
		Move();
	}
	vect_move *= .85f;
	start_move *= .95f;
	credit_move *= .95f;
	exit_move *= .95f;
	return STILL_PROCESSING;
}

int TitleScene::ExecuteFadeOut(){
	if (fade.AddAlpha(1.0f / 120.0f) == FADE_UNCLEAR){
		if (timer.Step() == FrameTimer::TIME_OUT)	{
			switch (select_i)
			{
			case 0:{
				CharacterSelectFactory cf;
				SceneFactory::Reserve(&cf);
				break;
			}
			case 1:{
				CreditFactory cf;
				SceneFactory::Reserve(&cf);
				break;
			}
			}
			return END_PROCESS;
		}
	}
	return STILL_PROCESSING;
}


