#include "Scene/CharacterSelectScene.h"

#include "Scene/Factory/StageSelectFactory.h"
#include "Input/Gamepad.h"
#include "Scene/CharacterSelectScene/Icon/SelectIcon.h"
#include "Scene/CharacterSelectScene/Cursor/SelectCursor.h"


CharacterSelectScene::CharacterSelectScene(){

	selectIcon = std::shared_ptr< SelectIcon > ( new SelectIcon );
	selectIcon->SetUp ();

	selectCursor = std::shared_ptr< SelectCursor > ( new SelectCursor );
	selectCursor->SetUp ();
}

CharacterSelectScene::~CharacterSelectScene(){
	selectIcon.reset();
	selectCursor.reset();
}

SCENE_STATUS CharacterSelectScene::Execute(){

	if (GamePad::getAnyGamePadPressed(BUTTON_X)){
		StageSelectFactory sf;
		SceneFactory::Reserve(&sf);
		return END_PROCESS;
	}

	selectCursor->Update ();

	return STILL_PROCESSING;
}

void CharacterSelectScene::Draw(){
	selectIcon->Draw ();
	selectCursor->Draw ();
}

