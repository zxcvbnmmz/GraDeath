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

	bgSprite = std::shared_ptr< Sprite > ( new Sprite );
	bgSprite->Create ( L"Resource/Scene/CharacterSelect/CharacterSelect_BG.png" );
	bgSprite->SetPosition ( 0, 0 );

	timer.Set ( 240 );
	countFlg = false;
}

SCENE_STATUS CharacterSelectScene::Execute(){

	if ( countFlg )
	{
		if ( timer.Step () == FrameTimer::TIME_OUT )
		{
			CharacterInfo info[ 4 ];
			for ( int i = 0; i < 4; i++ )
			{
//#ifdef _DEBUG
				if ( i == 0 )
				{
					info[ i ] = selectCursor->GetCharacterInfo ( i );
				}
				else
				{
					info[ i ].pType = CharacterInfo::PLAYER_TYPE::PLAYER_YELLOW;
					info[ i ].pcType = CharacterInfo::PC_TYPE::PC_PLAYER;
				}
//#else
//				info[ i ] = selectCursor->GetCharacterInfo ( i );
//#endif
			}
			CharacterInfoFunc::SetCharacterInfo ( info );
			StageSelectFactory sf;
			SceneFactory::Reserve ( &sf );
			return END_PROCESS;
		}
		return STILL_PROCESSING;
	}

	if ( selectCursor->AllSelectCheck () ||
		GamePad::getAnyGamePadPressed ( BUTTON_X )
//#ifdef _DEBUG
		|| Keyboard::CheckKey ( KC_ENTER ) == INPUT_PUSH
//#endif
		 ){
		countFlg = true;
	}

	selectCursor->Update ();
	return STILL_PROCESSING;
}

void CharacterSelectScene::Draw(){
	bgSprite->Draw ();
	selectCursor->Draw ();
}

