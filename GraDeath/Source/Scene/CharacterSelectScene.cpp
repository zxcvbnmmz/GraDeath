#include "Scene/CharacterSelectScene.h"

#include "Scene/Factory/StageSelectFactory.h"
#include "Input/Gamepad.h"
#include "Input/Keyboard.h"
#include "Scene/CharacterSelectScene/Icon/SelectIcon.h"
#include "Scene/CharacterSelectScene/Cursor/SelectCursor.h"
#include "Utility/Delegate.h"
#include "Object/Manager/PlayerManager.h"
#include "CharacterController/CharacterInfo.h"

CharacterSelectScene::CharacterSelectScene(){

	selectCursor = std::shared_ptr< SelectCursor > ( new SelectCursor );
	selectCursor->SetUp ();

	// ‰º‹L‚Í‚Ç‚¿‚ç‚Å‚àŒ‹‰Ê‚Í“¯‚¶Alist‚ÉŠÖ”‚ğ“Ë‚Á‚ñ‚Å‚¢‚é
	// (*list[0])();  ‚Ì‚æ‚¤‚ÉŠÖ”‚ğŒÄ‚×‚é
	//list.Add(Delegate<CharacterSelectScene>::Create(this, &CharacterSelectScene::ExecuteFadeOut));
	ADD_DELEGATE(CharacterSelectScene, this, &CharacterSelectScene::ExecuteFadeOut);
}

SCENE_STATUS CharacterSelectScene::Execute(){

	if ( selectCursor->AllSelectCheck () ||
		GamePad::getAnyGamePadPressed ( BUTTON_X ) ||
#ifdef _DEBUG
		INPUT_STATE::INPUT_PUSH == Keyboard::CheckKey ( KC_ENTER ) ){
#endif
		CharacterInfo info[4];
		for ( int i = 0; i < 4; i++ )
		{
			info[ i ].pType = CharacterInfo::PLAYER_TYPE::PLAYER_RED;
			info[ i ].pcType = CharacterInfo::PC_TYPE::PC_PLAYER;
			//info[ i ] = selectCursor->GetCharacterInfo ( i );
		}
		
		CharacterInfoFunc::SetCharacterInfo ( info );
		PlayerData date = &info;
		PlayerManager::Init ( ( PlayerData* )info );

		StageSelectFactory sf;
		SceneFactory::Reserve(&sf);
		return END_PROCESS;
	}

	selectCursor->Update ();
	return STILL_PROCESSING;
}

int CharacterSelectScene::ExecutePreDecide(){

}

int CharacterSelectScene::ExecuteFadeOut(){
	return 1;
}

void CharacterSelectScene::Draw(){
	selectCursor->Draw ();
}

