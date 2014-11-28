#include "Scene/GameScene/GameSceneUI.h"

GameSceneUI* GameSceneUI::ui = nullptr;

GameSceneUI::GameSceneUI(){
	// ‚±‚±‚ÅŠeUI‚Ì‰Šú‰»
	for (int i = 0; i < PLAYER_MAX; ++i){
		sprites[i][IDENTIFIER].Create(L"");
	}
}

GameSceneUI::~GameSceneUI(){
}

void GameSceneUI::Draw(){
	for (int i = 0; i < PLAYER_MAX; ++i){
		for (Sprite& sprite : sprites[i]){
			sprite.Draw();
		}
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


