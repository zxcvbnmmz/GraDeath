#include "Scene/GameScene/GameSceneUI.h"

GameSceneUI* GameSceneUI::ui = nullptr;

GameSceneUI::GameSceneUI(){
	// ‚±‚±‚ÅŠeUI‚Ì‰Šú‰»
	ground.Create ( L"Resource/UI/Game/player_ui_frame.png" );
	//for (int i = 0; i < PLAYER_MAX; ++i){
	//	sprites[i][IDENTIFIER].Create(L"");
	//}
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


