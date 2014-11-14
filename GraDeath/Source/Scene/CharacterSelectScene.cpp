#include "Scene/CharacterSelectScene.h"

#include "Scene/Factory/StageSelectFactory.h"
#include "Input/Gamepad.h"
#include "Input/Keyboard.h"
#include "Scene/CharacterSelectScene/Icon/SelectIcon.h"
#include "Scene/CharacterSelectScene/Cursor/SelectCursor.h"

#include "Utility/ScreenShot.h"
#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterInfo.h"

CharacterSelectScene::CharacterSelectScene(){

	selectCursor = std::shared_ptr< SelectCursor > ( new SelectCursor );
	selectCursor->SetUp ();
}

SCENE_STATUS CharacterSelectScene::Execute(){

	if ( selectCursor->AllSelectCheck () ||
		GamePad::getAnyGamePadPressed ( BUTTON_X )){// ||
		//Keyboard::CheckKey ( KC_ENTER ) ){

		CharacterInfo info[4];
		for ( int i = 0; i < 4; i++ )
		{
			info[ i ].pType = CharacterInfo::PLAYER_TYPE::PLAYER_RED;
			info[ i ].pcType = CharacterInfo::PC_TYPE::PC_PLAYER;
			//info[ i ] = selectCursor->GetCharacterInfo ( i );
		}
		PlayerData date = &info;
		PlayerManager::Init ( ( PlayerData* )info );

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
	return STILL_PROCESSING;
}

void CharacterSelectScene::Draw(){
	selectCursor->Draw ();
}

