#include "Scene/GameScene.h"
#include "Scene/Factory/ResultFactory.h"
#include "Input/Gamepad.h"
#include "Input\Keyboard.h"
#include "Stage/Stage.h"
#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterInfo.h"
#include "Utility/Delegate.h"
#include "Scene/GameScene/GameSceneUI.h"

GameScene::GameScene(){
	Stage::Initialize(0);
	
	PlayerManager::Init ( ( PlayerData* )CharacterInfoFunc::GetCharacterInfo () );

	GameSceneUI::Create ();
	/*
	AddFunction(this, &GameScene::ExecuteSample);
	AddFunction(this, &GameScene::DrawSample);
	AddFunction(this, &GameScene::DrawSample2);

	(*executes[0])();	// ExecuteSample
	(*draws[0])();		// DrawSample
	(*draws[1])();		// DrawSample2

	int i = 1;
	(*executes[i])();	// error
	(*draws[i])();		// DrawSample2

	int a = (*executes[0])();		// error
	int b = (int)(*executes[0])();	// not error
	*/
}

GameScene::~GameScene ()
{
	PlayerManager::Release();
	Stage::Release ();
	GameSceneUI::Release ();
}

SCENE_STATUS GameScene::Execute(){

//	if (GamePad::getAnyGamePadPressed(BUTTON_START) == INPUT_PRESS ||
//#ifdef _DEBUG
//		Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH){
//#endif
//		ResultFactory rf;
//		SceneFactory::Reserve(&rf);
//		return END_PROCESS;
//	}
//
//	PlayerManager::Update();

	return STILL_PROCESSING;
}

void GameScene::Draw(){
	Stage::Draw ();
	PlayerManager::Draw();
}

int GameScene::ExecuteSample(){
	return 1;
}

void GameScene::DrawSample(){

}

void GameScene::DrawSample2(){

}
