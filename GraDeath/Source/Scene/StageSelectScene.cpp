#include "Scene/StageSelectScene.h"

#include "Scene/Factory/GameFactory.h"
#include "Input/Gamepad.h"

StageSelectScene::StageSelectScene(){

}

SCENE_STATUS StageSelectScene::Execute(){

	if (GamePad::getAnyGamePadPressed(BUTTON_Y)){
		GameFactory gf;
		SceneFactory::Reserve(&gf);
		return END_PROCESS;
	}


	return STILL_PROCESSING;
}

void StageSelectScene::Draw(){

}

