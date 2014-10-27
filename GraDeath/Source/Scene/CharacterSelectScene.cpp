#include "Scene/CharacterSelectScene.h"

#include "Scene/Factory/StageSelectFactory.h"
#include "Input/Gamepad.h"


CharacterSelectScene::CharacterSelectScene(){

}

SCENE_STATUS CharacterSelectScene::Execute(){

	if (GamePad::getAnyGamePadPressed(BUTTON_X)){
		StageSelectFactory sf;
		SceneFactory::Reserve(&sf);
		return END_PROCESS;
	}

	return STILL_PROCESSING;
}

void CharacterSelectScene::Draw(){

}

