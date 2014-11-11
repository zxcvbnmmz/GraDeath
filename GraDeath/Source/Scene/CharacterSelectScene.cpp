#include "Scene/CharacterSelectScene.h"

#include "Scene/Factory/StageSelectFactory.h"
#include "Input/Gamepad.h"
#include "Input/Keyboard.h"
#include "Scene/CharacterSelectScene/Icon/SelectIcon.h"
#include "Scene/CharacterSelectScene/Cursor/SelectCursor.h"

#include "Utility/ScreenShot.h"


CharacterSelectScene::CharacterSelectScene(){

	selectIcon = std::shared_ptr< SelectIcon > ( new SelectIcon );
	selectIcon->SetUp ();

	selectCursor = std::shared_ptr< SelectCursor > ( new SelectCursor );
	selectCursor->SetUp ();
}

SCENE_STATUS CharacterSelectScene::Execute(){

	if ( selectCursor->AllSelectCheck () ||
		GamePad::getAnyGamePadPressed ( BUTTON_X ) ){
		StageSelectFactory sf;
		SceneFactory::Reserve(&sf);
		return END_PROCESS;
	}

	if (Keyboard::CheckKey(KC_O) == INPUT_PUSH){
		Utility::CreateScreenShot(L"Resource/ScreenShot/");
	}
	if (Keyboard::CheckKey(KC_P) == INPUT_PUSH){
		Utility::CreateScreenShot(L"Resource/ScreenShot/", L"GraDeath");
	}

	selectCursor->Update ();
	for ( int i = 0; i < 4; i++ )
	{
		D3DXVECTOR2 pos;
		if ( selectCursor->GetPadCursorPositon ( i, pos ) )
			selectIcon->CursorCollision ( i, pos );
	}

	return STILL_PROCESSING;
}

void CharacterSelectScene::Draw(){
	selectIcon->Draw ();
	selectCursor->Draw ();
}

