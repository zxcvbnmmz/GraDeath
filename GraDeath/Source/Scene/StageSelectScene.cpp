#include "Scene/StageSelectScene.h"

#include "Scene/Factory/GameFactory.h"
#include "Input/Gamepad.h"
#include "Input/Keyboard.h"

StageSelectScene::StageSelectScene(){

}

SCENE_STATUS StageSelectScene::Execute(){

	if (GamePad::getAnyGamePadPressed(BUTTON_Y)||
		Keyboard::CheckKey ( KC_ENTER ) ){
		GameFactory gf;
		SceneFactory::Reserve(&gf);
		return END_PROCESS;
	}


	return STILL_PROCESSING;
}

void StageSelectScene::Draw(){

}

