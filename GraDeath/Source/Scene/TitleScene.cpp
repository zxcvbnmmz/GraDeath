#include "Scene/TitleScene.h"
#include "Graphic/Camera/Camera.h"
#include "System/Window.h"

#include "Scene/Factory/CharacterSelectFactory.h"
#include "Scene/Factory/CaptureFactory.h"
#include "Input/Gamepad.h"
#include "Scene/Factory/TitleFactory.h"
#include "Scene/Factory/CreditFactory.h"

#include "Input\Keyboard.h"
#include "Utility/Delegate.h"
#include <time.h>

#include "Manager/BGMManager.h"

TitleScene::TitleScene(){
	srand((unsigned int)time(NULL));
	switch (rand() % 4)
	{
	case 0:
		sChara.Create(L"Resource/Texture/CharacterSelect/Chara1_img.png");
		break;
	case 1:
		sChara.Create(L"Resource/Texture/CharacterSelect/Chara2_img.png");
		break;
	case 2:
		sChara.Create(L"Resource/Texture/CharacterSelect/Chara3_img.png");
		break;
	default:
		sChara.Create(L"Resource/Texture/CharacterSelect/Chara4_img.png");
		break;
	}
	sStart.Create(L"Resource/Texture/Start.png");
	sCredit.Create(L"Resource/Texture/Credit.png");
	sExit.Create(L"Resource/Texture/Exit.png");
	sVector.Create(L"Resource/Texture/Vector.png");
	sBG1.Create(L"Resource/Texture/TitleBG1.png");
	sBG2.Create(L"Resource/Texture/TitleBG2.png");
	sCaution.Create(L"Resource/Texture/Caution.png");
	selectSE = Sound::CreateSE("Resource/Texture/selectSE.wav");
	cancelSE = Sound::CreateSE("Resource/Texture/cancelSE.wav");
	moveSE = Sound::CreateSE("Resource/Texture/moveSE.wav");
	start_pos = D3DXVECTOR2(700, 300);
	credit_pos = D3DXVECTOR2(800, 400);
	exit_pos = D3DXVECTOR2(800, 500);
	vect_pos = D3DXVECTOR2(600, 300);
	vect_move =
		start_move =
		credit_move =
		exit_move = D3DXVECTOR2(0, 0);
	tCount = 0;
	select_i = 0;

	AddFunction(this, &TitleScene::ExecuteCaution);
	AddFunction(this, &TitleScene::ExecuteSelect);
	AddFunction(this, &TitleScene::ExecuteFadeOut);
	AddFunction(this, &TitleScene::DrawCaution);
	AddFunction(this, &TitleScene::DrawSelect);
	AddFunction(this, &TitleScene::DrawFadeOut);
	currentState = CAUTION;
	//fade.SetAlpha(0);
	//timer.Set(60);
	fade.SetAlpha(1);
	timer.Set(60);
}

TitleScene::~TitleScene(){
}

SCENE_STATUS TitleScene::Execute(){
	int status = (int)(*executes[currentState])();
	//return STILL_PROCESSING;
	return (SCENE_STATUS)status;
}

void TitleScene::Draw(){
	(*draws[currentState])();
}

void TitleScene::DrawCaution(){
	sCaution.SetPosition(0, 0);
	sCaution.Draw();
	fade.Draw();
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
	sBG1.SetPosition(D3DXVECTOR2(0, 0));
	sBG2.SetPosition(D3DXVECTOR2(0, 0));
	sChara.SetPosition(D3DXVECTOR2(0, 0));
	sBG2.Draw();
	sChara.Draw();
	sBG1.Draw();
	sStart.SetPosition(start_pos + start_move);
	sCredit.SetPosition(credit_pos + credit_move);
	sExit.SetPosition(exit_pos + exit_move);
	sStart.Draw();
	sCredit.Draw();
	sExit.Draw();
	sVector.SetPositionY(vect_pos.y + select_i * 100 + vect_move.y);
	sVector.Draw();
}

void TitleScene::DrawFadeOut(){
	DrawSelect();
	fade.Draw();
}

void TitleScene::Move() {

	if (select_i < 0) {
		select_i = 2;
		vect_move = D3DXVECTOR2(0, -200);
	}
	else if (select_i >= 3)
	{
		select_i = 0;
		vect_move = D3DXVECTOR2(0, 200);
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

int TitleScene::ExecuteCaution(){
	static int step = 0;
	if (GamePad::getGamePadState(PAD_1, BUTTON_A, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH
#endif
		){
		step = 1;
		selectSE->Play();
	}
	switch (step)
	{
	case 0:
		if (fade.AddAlpha(-1.f / 120.f) == FADE_CLEAR){
			if (timer.Step() == FrameTimer::TIME_OUT) {
				step++;
				fade.SetAlpha(0);
				timer.Set(45);
			}
		}
		break;
	case 1:
		if (fade.AddAlpha(1.f / 120.f) == FADE_UNCLEAR){
			if (timer.Step() == FrameTimer::TIME_OUT) {
				step++;
			}
		}
		break;
	case 2:
		currentState = SELECT;
		if (rand() % 2 == 0)
			fade = Fade(L"Resource/Texture/Cut/in_cat01.png");
		else
			fade = Fade(L"Resource/Texture/Cut/in_cat02.png");
		fade.SetAlpha(0);
		timer.Set(60);
		BGMManager::GetInstance ()->Play ( "Resource/BGM/GDtitle.wav" );
		break;
	}
	return STILL_PROCESSING;
}

int TitleScene::ExecuteSelect(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_A, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH
#endif
		){
		switch (select_i){
		case 0:
		case 1:
			selectSE->Stop();
			selectSE->Play();
			currentState = FADE_OUT;
			break;
		case 2:
			cancelSE->Play();
			currentState = FADE_OUT;
			break;
		default:
			break;
		}
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_DOWN, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_DOWN) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		select_i++;
		vect_move += D3DXVECTOR2(0, -100);
		Move();
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_UP, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_UP) == INPUT_PUSH
#endif
		) {
		moveSE->Stop();
		moveSE->Play();
		select_i--;
		vect_move += D3DXVECTOR2(0, 100);
		Move();
	}

	if (Keyboard::CheckKey(KC_P) == INPUT_PUSH) {
		CaptureFactory cf;
		SceneFactory::Reserve (&cf);
		return END_PROCESS;
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
			case 2:
#ifdef _DEBUG
				TitleFactory tf;
				SceneFactory::Reserve(&tf);
				break;
#endif
				PostQuitMessage(0);
				break;
			}
			return END_PROCESS;
		}
	}
	return STILL_PROCESSING;
}


