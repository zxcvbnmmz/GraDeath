#include "Scene/CreditScene.h"
#include "Scene/Factory/TitleFactory.h"
#include "Input/Gamepad.h"
#include "Input\Keyboard.h"
#include "Utility/Delegate.h"

CreditScene::CreditScene(){
	AddFunction(this, &CreditScene::ExecutePage1);
	AddFunction(this, &CreditScene::ExecutePage2);
	AddFunction(this, &CreditScene::ExecutePage3);
	AddFunction(this, &CreditScene::ExecutePage4);
	AddFunction(this, &CreditScene::ExecutePage5);
	AddFunction(this, &CreditScene::ExecutePage6);
	AddFunction(this, &CreditScene::ExecutePage7);
	AddFunction(this, &CreditScene::ExecuteFadeOut);
	AddFunction(this, &CreditScene::DrawPage1);
	AddFunction(this, &CreditScene::DrawPage2);
	AddFunction(this, &CreditScene::DrawPage3);
	AddFunction(this, &CreditScene::DrawPage4);
	AddFunction(this, &CreditScene::DrawPage5);
	AddFunction(this, &CreditScene::DrawPage6);
	AddFunction(this, &CreditScene::DrawPage7);
	AddFunction(this, &CreditScene::DrawFadeOut);
	currentState = PAGE1;

	sPage1.Create(L"Resource/Scene/Credit/01.png");
	sPage2.Create(L"Resource/Scene/Credit/02.png");
	sPage3.Create(L"Resource/Scene/Credit/3.png");
	sPage4.Create(L"Resource/Scene/Credit/4.png");
	sPage5.Create(L"Resource/Scene/Credit/5.png");
	sPage6.Create(L"Resource/Scene/Credit/6.png");
	sPage7.Create(L"Resource/Scene/Credit/7.png");
	sBG.Create(L"Resource/Scene/Credit/kureji.png");
	cancelSE = Sound::CreateSE("Resource/Texture/cancelSE.wav");
	moveSE = Sound::CreateSE("Resource/Texture/moveSE.wav");
	int tempNum = rand() % 2;
	if (tempNum == 0)
		fade = std::shared_ptr< Fade >(new Fade(L"Resource/Texture/Cut/in_cat01.png"));
	else
		fade = std::shared_ptr< Fade >(new Fade(L"Resource/Texture/Cut/in_cat02.png"));
	fade->SetAlpha(0);
	sPos1 = D3DXVECTOR2(0, 0);
	sPos2 = D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
	sPos3 = D3DXVECTOR2(sPage1.GetDefaultSize().x * 2, 0);
	sPos4 = D3DXVECTOR2(sPage1.GetDefaultSize().x * 2, 0);
	sPos5 = D3DXVECTOR2(sPage1.GetDefaultSize().x * 2, 0);
	sPos6 = D3DXVECTOR2(sPage1.GetDefaultSize().x * 2, 0);
	sPos7 = D3DXVECTOR2(sPage1.GetDefaultSize().x * 2, 0);
	sBG.SetPosition(0, 0);
	mPos = D3DXVECTOR2(0, 0);
	sPage1.SetPosition(sPos1);
	sPage2.SetPosition(sPos2);
	sPage3.SetPosition(sPos3);
	sPage4.SetPosition(sPos4);
	sPage5.SetPosition(sPos5);
	sPage6.SetPosition(sPos6);
	sPage7.SetPosition(sPos7);
	pCenter = 0;
	pSide = sPage1.GetDefaultSize().x;
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
		&& currentState != 3
		){
		cancelSE->Play();
		currentState = FADE_OUT;
	}

	return (SCENE_STATUS)status;
}

void CreditScene::Draw(){
	sBG.Draw();
	(*draws[currentState])();
}

int CreditScene::ExecutePage1(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_RIGTH, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_RIGHT) == INPUT_PUSH
#endif
	){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE2;
		mPos += D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos1.x = -pSide;
		sPos2.x = pCenter;
		sPos3.x = pSide;
		sPos4.x = pSide * 2;
	}
	return STILL_PROCESSING;
}

int CreditScene::ExecutePage2(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_RIGTH, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_RIGHT) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE3;
		mPos += D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos1.x = -pSide * 2;
		sPos2.x = -pSide;
		sPos3.x = pCenter;
		sPos4.x = pSide;
		sPos5.x = pSide * 2;
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_LEFT, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_LEFT) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE1;
		mPos -= D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos1.x = pCenter;
		sPos2.x = pSide;
		sPos3.x = pSide * 2;
	}
	return STILL_PROCESSING;
}

int CreditScene::ExecutePage3(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_RIGTH, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_RIGHT) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE4;
		mPos += D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos2.x = -pSide * 2;
		sPos3.x = -pSide;
		sPos4.x = pCenter;
		sPos5.x = pSide;
		sPos6.x = pSide * 2;
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_LEFT, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_LEFT) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE2;
		mPos -= D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos1.x = -pSide;
		sPos2.x = pCenter;
		sPos3.x = pSide;
		sPos4.x = pSide * 2;
	}
	return STILL_PROCESSING;
}

int CreditScene::ExecutePage4(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_RIGTH, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_RIGHT) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE5;
		mPos += D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos3.x = -pSide * 2;
		sPos4.x = -pSide;
		sPos5.x = pCenter;
		sPos6.x = pSide;
		sPos7.x = pSide * 2;
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_LEFT, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_LEFT) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE3;
		mPos -= D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos1.x = -pSide * 2;
		sPos2.x = -pSide;
		sPos3.x = pCenter;
		sPos4.x = pSide;
		sPos5.x = pSide * 2;
	}
	return STILL_PROCESSING;
}

int CreditScene::ExecutePage5(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_RIGTH, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_RIGHT) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE6;
		mPos += D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos4.x = -pSide * 2;
		sPos5.x = -pSide;
		sPos6.x = pCenter;
		sPos7.x = pSide;
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_LEFT, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_LEFT) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE4;
		mPos -= D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos2.x = -pSide * 2;
		sPos3.x = -pSide;
		sPos4.x = pCenter;
		sPos5.x = pSide;
		sPos6.x = pSide * 2;
	}
	return STILL_PROCESSING;
}

int CreditScene::ExecutePage6(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_RIGTH, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_RIGHT) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE7;
		mPos += D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos5.x = -pSide * 2;
		sPos6.x = -pSide;
		sPos7.x = pCenter;
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_LEFT, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_LEFT) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE5;
		mPos -= D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos5.x = pCenter;
		sPos6.x = pSide;
		sPos7.x = pSide * 2;
	}
	return STILL_PROCESSING;
}

int CreditScene::ExecutePage7(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_LEFT, 0) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_LEFT) == INPUT_PUSH
#endif
		){
		moveSE->Stop();
		moveSE->Play();
		currentState = PAGE6;
		mPos -= D3DXVECTOR2(sPage1.GetDefaultSize().x, 0);
		sPos5.x = -pSide;
		sPos6.x = pCenter;
		sPos7.x = pSide;
	}
	return STILL_PROCESSING;
}

int CreditScene::ExecuteFadeOut(){
	if (fade->AddAlpha(1.f / 120.f) == FADE_UNCLEAR)
	{
		TitleFactory cf;
		SceneFactory::Reserve(&cf);
		return END_PROCESS;
	}
	return STILL_PROCESSING;
}

void CreditScene::DrawPage1(){
	sPage1.SetPosition(sPos1 + mPos);
	sPage2.SetPosition(sPos2 + mPos);
	sPage1.Draw();
	sPage2.Draw();
}

void CreditScene::DrawPage2(){
	sPage1.SetPosition(sPos1 + mPos);
	sPage2.SetPosition(sPos2 + mPos);
	sPage3.SetPosition(sPos3 + mPos);
	sPage1.Draw();
	sPage2.Draw();
	sPage3.Draw();
}

void CreditScene::DrawPage3(){
	//sPage1.SetPosition(sPos1 + mPos);
	sPage2.SetPosition(sPos2 + mPos);
	sPage3.SetPosition(sPos3 + mPos);
	sPage4.SetPosition(sPos4 + mPos);
	//sPage5.SetPosition(sPos5 + mPos);
	//sPage1.Draw();
	sPage2.Draw();
	sPage3.Draw();
	sPage4.Draw();
	//sPage5.Draw();
}

void CreditScene::DrawPage4(){
	sPage3.SetPosition(sPos3 + mPos);
	sPage4.SetPosition(sPos4 + mPos);
	sPage5.SetPosition(sPos5 + mPos);
	sPage3.Draw();
	sPage4.Draw();
	sPage5.Draw();
}

void CreditScene::DrawPage5(){
	sPage4.SetPosition(sPos4 + mPos);
	sPage5.SetPosition(sPos5 + mPos);
	sPage6.SetPosition(sPos6 + mPos);
	sPage4.Draw();
	sPage5.Draw();
	sPage6.Draw();
}

void CreditScene::DrawPage6(){
	sPage5.SetPosition(sPos5 + mPos);
	sPage6.SetPosition(sPos6 + mPos);
	sPage7.SetPosition(sPos7 + mPos);
	sPage5.Draw();
	sPage6.Draw();
	sPage7.Draw();
}

void CreditScene::DrawPage7(){
	sPage6.SetPosition(sPos6 + mPos);
	sPage7.SetPosition(sPos7 + mPos);
	sPage6.Draw();
	sPage7.Draw();
}

void CreditScene::DrawFadeOut(){
	fade->Draw();
}