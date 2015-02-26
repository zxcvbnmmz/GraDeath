#include "Scene/GameScene.h"

#include "Scene/Factory/TitleFactory.h"


#include "Scene/Factory/ResultFactory.h"
#include "Input/Gamepad.h"
#include "Input\Keyboard.h"
#include "Stage/Stage.h"
#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterInfo.h"
#include "Utility/Delegate.h"
#include "Scene/GameScene/GameSceneUI.h"
#include "Manager/HitPointManager.h"
#include "Collision/Collision.h"

#include "World/World.h"

char* stageBGMName[ ] =
{
	"Resource/BGM/RedBGM.wav",
	"Resource/BGM/StageBGM_Chara1.wav",
	"Resource/BGM/ShirokuroBGM.wav",
	"Resource/BGM/YellowBGM.wav",
	"Resource/BGM/NOCollarBGM.wav",
};

GameScene::GameScene() :currentState(FADE_IN) {
	Stage::Initialize(0);
	
	PlayerManager::Init ( ( PlayerData* )CharacterInfoFunc::GetCharacterInfo () );

	GameSceneUI::Create ();
	GameSceneUI::Create ()->SetPlayerIcon ( CharacterInfoFunc::GetCharacterInfo () );
	
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

	//int temp = Stage::GetStageNum ();
	//bgm = Sound::CreateBGM ( stageBGMName[ Stage::GetStageNum () ] );

	switch (Stage::GetStageNum())
	{
	case 0:
		bgm = Sound::CreateBGM("Resource/BGM/RedBGM.wav");
		break;
	case 1:
		bgm = Sound::CreateBGM("Resource/BGM/StageBGM_Chara1.wav");
		break;
	case 2:
		bgm = Sound::CreateBGM("Resource/BGM/ShirokuroBGM.wav");
		break;

	case 3:
		bgm = Sound::CreateBGM ( "Resource/BGM/YellowBGM.wav" );
		break;

	default:
		bgm = Sound::CreateBGM("Resource/BGM/NOCollarBGM2.wav");
		break;
	}
	// 最初の引数がループ開始点
	// 第二引数がループ終了点
	// 第三引数がループ回数（255で無限ループ）
	bgm->SetLoop ( 0, 0, 255 );
}

GameScene::~GameScene ()
{
	stageCall.Release();
	bgm->~BGM();
	PlayerManager::Release();
	Stage::Release ();
	GameSceneUI::Release ();
}

SCENE_STATUS GameScene::Execute(){

	int status = (int)(*executes[currentState])();



	if (GamePad::getAnyGamePadPressed(BUTTON_START) == INPUT_PRESS 
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_R) == INPUT_PUSH
#endif
		){

		//ResultFactory rf;
		TitleFactory rf;

		SceneFactory::Reserve(&rf);
		return END_PROCESS;
	}

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
		bgm->Play ();
	}

	//bgm->Play();

	return STILL_PROCESSING;
}

int GameScene::ExecuteButtle(){

    PlayerManager::Update();
    if (Stage::GetStageHP() > 0){
        // ここで通常作業
        //if ()
        World::SetGravity(0, 95);
    }
    else{
        World::SetGravity(0, 25);
        Stage::DettachFixture();
//        Stage::SetCharaType();
//        PlayerManager::AllPlayerMove(0,10);
        
//        PlayerManager::OnPlayerPos(Stage::StageBrakePlayerNum(),300,300);
    }
    if (Stage::GetSkillEnd() == true){

        Stage::SetSkillEnd(false);
        for (int i = 0; i < 4; i++)
            PlayerManager::OnPlayerPos(i, 2+(10*i), 0);
    }

	if (HitPointManager::IsOnlyOne()){
		currentState = SURVIVE_ONE;
		stageCall.Initialize(true);

	}

	return STILL_PROCESSING;
}

int GameScene::ExecuteEndCall(){
	if (stageCall.Update() == StageCall::FINISHED ||
		GamePad::getAnyGamePadPressed ( BUTTON_START ) == INPUT_PRESS ){

		ResultFactory rf;
		SceneFactory::Reserve(&rf);
		bgm->Stop();


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
	GameSceneUI::Create()->Draw();
    Stage::FadeDraw();
}

void GameScene::DrawEndCall(){
	DrawButtle();
	stageCall.Draw();
}
