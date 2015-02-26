#include "Scene/CreditScene.h"
#include "Scene/Factory/TitleFactory.h"
#include "Input/Gamepad.h"
#include "Input\Keyboard.h"
#include "Utility/Delegate.h"

CreditScene::CreditScene(){
	AddFunction(this, &CreditScene::ExecutePage1);
	AddFunction(this, &CreditScene::ExecutePage2);
	AddFunction(this, &CreditScene::ExecutePage3);
	AddFunction(this, &CreditScene::DrawPage1);
	AddFunction(this, &CreditScene::DrawPage2);
	AddFunction(this, &CreditScene::DrawPage3);
	currentState = PAGE1;

	sPage1.Create(L"Resource/Scene/Credit/1.png");
	sPage2.Create(L"Resource/Scene/Credit/2.png");
	sPage3.Create(L"Resource/Scene/Credit/3.png");
	sPos1 = D3DXVECTOR2(0, 0);
	sPos2 = D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
	sPos3 = D3DXVECTOR2(sPage1.GetDefaultSize().x * 2, 0);
	mPos = D3DXVECTOR2(0, 0);
	sPage1.SetPosition(sPos1);
	sPage2.SetPosition(sPos2);
	sPage3.SetPosition(sPos3);
}

CreditScene::~CreditScene(){

}

SCENE_STATUS CreditScene::Execute(){
	mPos *= .9;
	int status = (int)(*executes[currentState])();

	if (GamePad::getAnyGamePadPressed(BUTTON_B) == INPUT_PRESS
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_R) == INPUT_STATE::INPUT_PUSH
#endif
		){
		TitleFactory cf;
		SceneFactory::Reserve(&cf);
		return END_PROCESS;
	}

	return (SCENE_STATUS)status;
}

void CreditScene::Draw(){
	(*draws[currentState])();
	sPage1.SetPosition(sPos1 + mPos);
	sPage2.SetPosition(sPos2 + mPos);
	sPage3.SetPosition(sPos3 + mPos);
	sPage1.Draw();
	sPage2.Draw();
	sPage3.Draw();
}

int CreditScene::ExecutePage1(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_RIGTH, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_RIGHT) == INPUT_PUSH
#endif
	){
		currentState = PAGE2;
		mPos += D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos1.x = -sPage1.GetDefaultSize().x;
		sPos2.x = 0;
		sPos3.x = sPage1.GetDefaultSize().x;
	}
	return STILL_PROCESSING;
}

int CreditScene::ExecutePage2(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_RIGTH, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_RIGHT) == INPUT_PUSH
#endif
	){
		currentState = PAGE3;
		mPos += D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos1.x = -sPage1.GetDefaultSize().x * 2;
		sPos2.x = -sPage1.GetDefaultSize().x;
		sPos3.x = 0;
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_LEFT, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_LEFT) == INPUT_PUSH
#endif
	){
		currentState = PAGE1;
		mPos -= D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos1.x = 0;
		sPos2.x = sPage1.GetDefaultSize().x;
		sPos3.x = sPage1.GetDefaultSize().x * 2;
	}
	return STILL_PROCESSING;
}

int CreditScene::ExecutePage3(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_LEFT, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_LEFT) == INPUT_PUSH
#endif
		){
		currentState = PAGE2;
		mPos -= D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos1.x = -sPage1.GetDefaultSize().x;
		sPos2.x = 0;
		sPos3.x = sPage1.GetDefaultSize().x;
	}
	return STILL_PROCESSING;
}

void CreditScene::DrawPage1(){
}

void CreditScene::DrawPage2(){
}

void CreditScene::DrawPage3(){
}