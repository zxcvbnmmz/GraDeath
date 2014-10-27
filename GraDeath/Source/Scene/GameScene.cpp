#include "Scene/GameScene.h"

#include "Scene/Factory/ResultFactory.h"
#include "Input/Gamepad.h"

GameScene::GameScene(){

}

SCENE_STATUS GameScene::Execute(){

	if (GamePad::getAnyGamePadPressed(BUTTON_A)){
		ResultFactory rf;
		SceneFactory::Reserve(&rf);
		return END_PROCESS;
	}


	return STILL_PROCESSING;
}

void GameScene::Draw(){

}
