#include "D2D/Sprite/Sprite.h"
#include "Scene/ResultScene.h"

#include "Scene/Factory/CharacterSelectFactory.h"
#include "Input/Gamepad.h"

ResultScene::ResultScene(){
}

SCENE_STATUS ResultScene::Execute(){

	if (GamePad::getAnyGamePadPressed(BUTTON_B)){
		CharacterSelectFactory cf;
		SceneFactory::Reserve(&cf);
		return END_PROCESS;
	}


	return STILL_PROCESSING;
}

void ResultScene::Draw(){

}
