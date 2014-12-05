#include "Scene/GameScene/GameSceneUI.h"
#include "Manager/HitPointManager.h"

GameSceneUI* GameSceneUI::ui = nullptr;

wchar_t* playerIconUI[ ] =
{
	L"Resource/UI/Game/player_icon_1.png",
	L"Resource/UI/Game/player_icon_2.png",
	L"Resource/UI/Game/player_icon_3.png",
	L"Resource/UI/Game/player_icon_4.png",
};

GameSceneUI::GameSceneUI(){
	// Ç±Ç±Ç≈äeUIÇÃèâä˙âª
	ground.Create ( L"Resource/UI/Game/player_ui_frame.png" );
	hpBar.Create (L"Resource/UI/Game/hpbar.png");
	deadlyGage.Create ( L"Resource/UI/Game/deadlygage.png" );
	for (int i = 0; i < PLAYER_MAX; ++i){
		sprites[ i ][ IDENTIFIER ].Create ( playerIconUI[ i ] );
	}
}

GameSceneUI::~GameSceneUI(){
}

void GameSceneUI::Draw(){
	D3DXVECTOR2 tempPos;
	D3DXVECTOR2 gageSize;
	for (int i = 0; i < PLAYER_MAX; ++i){
		// Frame
		ground.SetPosition ( 50 + ( 320 * (float)i), 630 );
		ground.Draw ();

		tempPos = ground.GetPosition ();

		// Icon
		sprites[ i ][ IDENTIFIER ].SetPosition ( tempPos.x + 200, tempPos.y + 15 );
		sprites[ i ][ IDENTIFIER ].Draw ();
		//for (Sprite& sprite : sprites[i]){
		//	sprite[ IDENTIFIER ].SetPosition ( tempPos.x + 150, tempPos.y + 15 );
		//	sprite[ IDENTIFIER ].Draw ();
		//}

		// HPBar
		gageSize = hpBar.GetDefaultSize ();
		gageSize.x *= HitPointManager::GetHitPoint ( i );
		hpBar.SetPosition ( tempPos.x + 15, tempPos.y + 15 );
		hpBar.SetSize ( gageSize );
		hpBar.Draw ();

		// DeadlyGage
		gageSize = deadlyGage.GetDefaultSize ();
		deadlyGage.SetPosition ( tempPos.x + 15, tempPos.y + 50 );
		deadlyGage.SetSize ( gageSize );
		deadlyGage.Draw ();
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


