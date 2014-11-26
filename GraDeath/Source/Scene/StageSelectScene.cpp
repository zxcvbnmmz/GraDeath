#include "Scene/StageSelectScene.h"

#include "Scene/Factory/GameFactory.h"
#include "Input/Gamepad.h"
#include "Input/Keyboard.h"
#include "Scene/StageSelectScene/StageIcon.h"

StageSelectScene::StageSelectScene(){
	stageIcon = std::shared_ptr< StageIcon > ( new StageIcon );
	stageIcon->SetUp ();
}

SCENE_STATUS StageSelectScene::Execute(){

	if (GamePad::getAnyGamePadPressed(BUTTON_Y)||
		INPUT_STATE::INPUT_PUSH == Keyboard::CheckKey ( KC_ENTER ) ){
		GameFactory gf;
		SceneFactory::Reserve(&gf);
		return END_PROCESS;
	}


	return STILL_PROCESSING;
}

void StageSelectScene::Draw(){
	stageIcon->Draw ();
}

