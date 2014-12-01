#include "Scene/GameScene.h"
#include "Scene/Factory/ResultFactory.h"
#include "Input/Gamepad.h"
#include "Input\Keyboard.h"
#include "Stage/Stage.h"
#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterInfo.h"

GameScene::GameScene(){
	Stage::Initialize(0);
	
	PlayerManager::Init ( ( PlayerData* )CharacterInfoFunc::GetCharacterInfo () );
}

GameScene::~GameScene ()
{
	PlayerManager::Release();
	Stage::Release ();
}

SCENE_STATUS GameScene::Execute(){

	if (GamePad::getAnyGamePadPressed(BUTTON_START) == INPUT_PRESS ||
#ifdef _DEBUG
		Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH){
#endif
		ResultFactory rf;
		SceneFactory::Reserve(&rf);
		return END_PROCESS;
	}

	PlayerManager::Update();


	return STILL_PROCESSING;
}

void GameScene::Draw(){
	Stage::Draw ();
	PlayerManager::Draw();
}

