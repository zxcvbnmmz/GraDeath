#include "Scene/StageSelectScene.h"

#include "Scene/Factory/GameFactory.h"
#include "Input/Gamepad.h"
#include "Input/Keyboard.h"
#include "Scene/StageSelectScene/StageIcon.h"
#include "Scene/Factory/CharacterSelectFactory.h"

#include "Stage/Stage.h"
#include "Direction/Fade.h"
#include "Utility/Delegate.h"
#include "Direction/Fade.h"

#include <stdlib.h>

#include "Manager/BGMManager.h"


StageSelectScene::StageSelectScene(){
	stageIcon = std::shared_ptr< StageIcon > ( new StageIcon );
	stageIcon->SetUp ();
	bgSprite = std::shared_ptr< Sprite > ( new Sprite );
	bgSprite->Create (L"Resource/Scene/StageSelect/StageSelect_BG.png");
	bgSprite->SetPosition ( 0, 0 );

	//loadSprite = std::shared_ptr< Sprite > ( new Sprite );
	//loadSprite->Create ( L"Resource/Scene/StageSelect/StageSelect_BG.png" );
	//loadSprite->SetPosition ( 0, 0 );
	
	int tempNum = rand () % 2;
	if ( tempNum == 0 )
		fade = std::shared_ptr< Fade > ( new Fade ( L"Resource/Texture/Cut/in_cat01.png" ) );
	else
		fade = std::shared_ptr< Fade > ( new Fade ( L"Resource/Texture/Cut/in_cat02.png" ) );
	fade->SetAlpha ( 0 );
	currentState = SELECT_MAIN;

	AddFunction ( this, &StageSelectScene::ExecuteMain );
	AddFunction ( this, &StageSelectScene::ExecuteOut );
	AddFunction ( this, &StageSelectScene::DrawMain );
	AddFunction ( this, &StageSelectScene::DrawOut );
}

SCENE_STATUS StageSelectScene::Execute(){

	int status = ( int )( *executes[ currentState ] )( );
	return ( SCENE_STATUS )status;
}

void StageSelectScene::Draw(){
	( *draws[ currentState ] )( );
	//bgSprite->Draw ();
	//stageIcon->Draw ();
}

int StageSelectScene::ExecuteMain ()
{
	if ( GamePad::getGamePadState ( PAD_1, BUTTON_A ) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey ( KC_ENTER ) == INPUT_PUSH
#endif
		){
		Stage::SetStagenum ( stageIcon->GetStageNum () );
		currentState = SELECT_OUT;
		//return END_PROCESS;
	}
	else if ( GamePad::getGamePadState ( PAD_1, BUTTON_B ) == INPUT_PUSH )
	{
		CharacterSelectFactory cf;
		SceneFactory::Reserve ( &cf );
		//currentState = SELECT_OUT;
		return END_PROCESS;
	}
	stageIcon->Update ();
	return STILL_PROCESSING;
}

int StageSelectScene::ExecuteOut ()
{
	if ( fade->AddAlpha ( 1.f / 120.f ) == FADE_UNCLEAR )
	{
		BGMManager::GetInstance ()->Stop ( "Resource/BGM/GDtitle.wav" );
		GameFactory gf;
		SceneFactory::Reserve ( &gf );
		return END_PROCESS;
	}
	return STILL_PROCESSING;
}

void StageSelectScene::DrawMain ()
{
	bgSprite->Draw ();
	stageIcon->Draw ();
}

void StageSelectScene::DrawOut ()
{
	bgSprite->Draw ();
	stageIcon->Draw ();

	fade->Draw ();
	//loadSprite->Draw ();
}