#include "Scene/GameScene/GameSceneUI.h"

GameSceneUI* GameSceneUI::ui = nullptr;

wchar_t* playerIconUI[ ] =
{
	L"Resource/UI/Game/player_icon_1.bin",
	L"Resource/UI/Game/player_icon_2.bin",
	L"Resource/UI/Game/player_icon_3.bin",
	L"Resource/UI/Game/player_icon_4.bin",
};

GameSceneUI::GameSceneUI(){
	// Ç±Ç±Ç≈äeUIÇÃèâä˙âª
	ground.Create ( L"Resource/UI/Game/player_ui_frame.png" );
	for (int i = 0; i < PLAYER_MAX; ++i){
		sprites[ i ][ IDENTIFIER ].Create ( playerIconUI[ i ] );
	}
}

GameSceneUI::~GameSceneUI(){
}

void GameSceneUI::Draw(){
	for (int i = 0; i < PLAYER_MAX; ++i){
		ground.SetPosition ( 50 + ( 320 * i), 630 );
		ground.Draw ();

		//for (Sprite& sprite : sprites[i]){
		//	sprite.Draw();
		//}
	}
}

GameSceneUI* GameSceneUI::Create(){
	if (ui == nullptr){
		ui = new GameSceneUI;
		ObjectPoolManager::GetInstance()->GetCurrentPool()->Add(ui);
	}

	return ui;
}

void GameSceneUI::Release(){
	ObjectPoolManager::GetInstance()->GetCurrentPool()->Erase(ui);
}


