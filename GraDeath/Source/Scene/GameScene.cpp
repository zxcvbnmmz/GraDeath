#include "Scene/GameScene.h"
#include "Scene/Factory/ResultFactory.h"
#include "Input/Gamepad.h"
#include "Input\Keyboard.h"
#include "Stage/Stage.h"
#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterInfo.h"
#include "Utility/Delegate.h"
#include "Scene/GameScene/GameSceneUI.h"
#include "Manager/HitPointManager.h"
#include "Manager/SkillManager.h"

#include "World/World.h"

GameScene::GameScene() :currentState(FADE_IN) {
	Stage::Initialize(0);
	
	PlayerManager::Init ( ( PlayerData* )CharacterInfoFunc::GetCharacterInfo () );

	GameSceneUI::Create ();
	
	AddFunction(this, &GameScene::ExecuteFadeIn);
	AddFunction(this, &GameScene::ExecuteStageCall);
	AddFunction(this, &GameScene::ExecuteButtle);
	AddFunction(this, &GameScene::ExecuteEndCall);
	AddFunction(this, &GameScene::DrawFadeIn);
	AddFunction(this, &GameScene::DrawStageCall);
	AddFunction(this, &GameScene::DrawButtle);
	AddFunction(this, &GameScene::DrawEndCall);

	stageCall.Initialize(false);

	stageTimer = 300;
}

GameScene::~GameScene ()
{
	stageCall.Release();

	PlayerManager::Release();
	Stage::Release ();
	GameSceneUI::Release ();
	SkillManager::Release ();
}

SCENE_STATUS GameScene::Execute(){

	int status = (int)(*executes[currentState])();
//	if (GamePad::getAnyGamePadPressed(BUTTON_START) == INPUT_PRESS 
//#ifdef _DEBUG
//		|| Keyboard::CheckKey(KC_R) == INPUT_PUSH
//#endif
//		){
//		ResultFactory rf;
//		SceneFactory::Reserve(&rf);
//		return END_PROCESS;
//	}

	return (SCENE_STATUS)(status);
}

void GameScene::Draw(){
	(*draws[currentState])();

#ifdef _DEBUG
	World::DrawDebugData(&drawer);
#endif
}

int GameScene::ExecuteFadeIn(){
	//ここでフェード作業
	currentState = STAGE_CALL;

	return STILL_PROCESSING;
}

int GameScene::ExecuteStageCall(){
	// ここでステージコール作業
	if (stageCall.Update() == StageCall::FINISHED){
		currentState = BUTTLE;
	}

	return STILL_PROCESSING;
}

int GameScene::ExecuteButtle(){
	
    if (Stage::GetStageHP() > 0){
        // ここで通常作業
        PlayerManager::Update();
        SkillManager::Update();
    }
    else{
        PlayerManager::AllPlayerMove(10, 10);
        PlayerManager::OnPlayerPos(1, 300, 300);
//        PlayerManager::OnPlayerPos(Stage::StageBrakePlayerNum(),300,300);
    }

	// ここでエンドコールへ移行(コメントアウト)
	//if (stageTimer-- < 0){
	//	currentState = END_CALL;
	//	stageCall.Initialize(true);
	//	}
	return STILL_PROCESSING;
}

int GameScene::ExecuteEndCall(){
	if (stageCall.Update() == StageCall::FINISHED){
		return END_PROCESS;
	}
	return STILL_PROCESSING;
}

void GameScene::DrawFadeIn(){
	DrawButtle();
}

void GameScene::DrawStageCall(){
	DrawButtle();
	stageCall.Draw();
}

void GameScene::DrawButtle(){
	Stage::Draw();
	PlayerManager::Draw();
	SkillManager::Draw ();
//    Special();
	GameSceneUI::Create()->Draw();
}

void GameScene::DrawEndCall(){
	DrawButtle();
	stageCall.Draw();
}
