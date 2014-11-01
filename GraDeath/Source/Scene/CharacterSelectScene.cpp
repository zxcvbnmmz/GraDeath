#include "Scene/CharacterSelectScene.h"

#include "Scene/Factory/StageSelectFactory.h"
#include "Input/Gamepad.h"
#include "Scene/CharacterSelectScene/Icon/SelectIcon.h"


CharacterSelectScene::CharacterSelectScene(){

	selectIcon = std::shared_ptr< SelectIcon > ( new SelectIcon );
	selectIcon->SetUp ();

	//characterIcon = std::shared_ptr< CharacterIcon > ( new CharacterIcon );
	//characterIcon->SetUp ();
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
	selectIcon->Draw ();
	//characterIcon->Draw ();
}

