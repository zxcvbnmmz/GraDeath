#include "Scene/StageSelectScene.h"

#include "Scene/Factory/GameFactory.h"
#include "Input/Gamepad.h"
#include "Input/Keyboard.h"
#include "Scene/StageSelectScene/StageIcon.h"

StageSelectScene::StageSelectScene(){
	stageIcon = std::shared_ptr< StageIcon > ( new StageIcon );
	stageIcon->SetUp ();
	bgSprite = std::shared_ptr< Sprite > ( new Sprite );
	bgSprite->Create (L"Resource/Scene/StageSelect/StageSelect_BG.png");
	bgSprite->SetPosition ( 0, 0 );
}

SCENE_STATUS StageSelectScene::Execute(){

	if ( GamePad::getGamePadState ( PAD_1, BUTTON_A ) == INPUT_PUSH ||
		INPUT_STATE::INPUT_PUSH == Keyboard::CheckKey ( KC_ENTER ) ){
		GameFactory gf;
		SceneFactory::Reserve(&gf);
		return END_PROCESS;
	}
	stageIcon->Update ();

	return STILL_PROCESSING;
}

void StageSelectScene::Draw(){
	bgSprite->Draw ();
	stageIcon->Draw ();
}

