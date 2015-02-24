#include "Scene/StageSelectScene.h"

#include "Scene/Factory/GameFactory.h"
#include "Input/Gamepad.h"
#include "Input/Keyboard.h"
#include "Scene/StageSelectScene/StageIcon.h"
#include "Scene/Factory/CharacterSelectFactory.h"

#include "Stage/Stage.h"

StageSelectScene::StageSelectScene(){
	stageIcon = std::shared_ptr< StageIcon > ( new StageIcon );
	stageIcon->SetUp ();
	bgSprite = std::shared_ptr< Sprite > ( new Sprite );
	bgSprite->Create (L"Resource/Scene/StageSelect/StageSelect_BG.png");
	bgSprite->SetPosition ( 0, 0 );
}

SCENE_STATUS StageSelectScene::Execute(){

	if ( GamePad::getGamePadState ( PAD_1, BUTTON_A ) == INPUT_PUSH
#ifdef _DEBUG
		|| Keyboard::CheckKey ( KC_ENTER ) == INPUT_PUSH
#endif
		){
		Stage::SetStagenum ( stageIcon->GetStageNum() );
		GameFactory gf;
		SceneFactory::Reserve(&gf);
		return END_PROCESS;
	}
	else if ( GamePad::getGamePadState ( PAD_1, BUTTON_B ) == INPUT_PUSH )
	{
		CharacterSelectFactory cf;
		SceneFactory::Reserve ( &cf );
		return END_PROCESS;
	}
	stageIcon->Update ();

	return STILL_PROCESSING;
}

void StageSelectScene::Draw(){
	bgSprite->Draw ();
	stageIcon->Draw ();
}

