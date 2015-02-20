#include "Scene/GameScene/GameSceneUI.h"
#include "Manager/HitPointManager.h"
#include "Manager/SkillManager.h"

GameSceneUI* GameSceneUI::ui = nullptr;

wchar_t* playerIconUI[ ] =
{
	L"Resource/UI/Game/player_icon_1.png",
	L"Resource/UI/Game/player_icon_2.png",
	L"Resource/UI/Game/player_icon_3.png",
	L"Resource/UI/Game/player_icon_4.png",
};

wchar_t* skillIconUI[ ] =
{
	L"Resource/UI/Game/skill_first.png",
	L"Resource/UI/Game/skill_scond.png",
	L"Resource/UI/Game/skill_third.png",
};

GameSceneUI::GameSceneUI(){
	// Ç±Ç±Ç≈äeUIÇÃèâä˙âª
	ground.Create ( L"Resource/UI/Game/player_ui_frame.png" );
	barBack.Create ( L"Resource/UI/Game/hpbar_back.png" );
	barFront.Create ( L"Resource/UI/Game/hpbar_frame.png" );
	gageUI[ HP_BAR ].Create ( L"Resource/UI/Game/hpbar.png" );
	gageUI[ DEADLY_GAGE ].Create ( L"Resource/UI/Game/deadlygage.png" );
	for (int i = 0; i < PLAYER_MAX; ++i){
		sprites[ i ][ IDENTIFIER ].Create ( playerIconUI[ i ] );
	}
	for ( int i = 0; i < SKILL_ID::SKILL_MAX; i++ )
	{
		skillIcon[ i ].Create ( skillIconUI[ i ] );
	}
	skillMask.Create ( L"Resource/UI/Game/skill_mask.png" );
	skillMask.SetAlpha ( 0.6f );
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
		barBack.SetPosition ( tempPos.x + 15, tempPos.y + 15 );
		barBack.Draw ();
		gageSize = gageUI[ HP_BAR ].GetDefaultSize ();
		gageSize.x *= HitPointManager::GetHitPoint ( i );
		gageUI[ HP_BAR ].SetPosition ( tempPos.x + 15, tempPos.y + 15 );
		gageUI[ HP_BAR ].SetSize ( gageSize );
		gageUI[ HP_BAR ].Draw ();
		barFront.SetPosition ( tempPos.x + 15, tempPos.y + 15 );
		barFront.Draw ();

		// DeadlyGage
		float tempGage = ( 1.0f - HitPointManager::GetHitPoint ( i ) ) * 4.0f;
		if ( tempGage >= 1.0f )
			tempGage = 1.0f;

		barBack.SetPosition ( tempPos.x + 15, tempPos.y + 50 );
		barBack.Draw ();
		gageSize = gageUI[ DEADLY_GAGE ].GetDefaultSize ();
		gageSize.x *= tempGage;
		gageUI[ DEADLY_GAGE ].SetPosition ( tempPos.x + 15, tempPos.y + 50 );
		gageUI[ DEADLY_GAGE ].SetSize ( gageSize );
		gageUI[ DEADLY_GAGE ].Draw ();
		barFront.SetPosition ( tempPos.x + 15, tempPos.y + 50 );
		barFront.Draw ();

		DrawSkillUI ( i, tempPos );
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
	ui = nullptr;
}


void GameSceneUI::DrawSkillUI ( int _num, D3DXVECTOR2& _pos )
{
	D3DXVECTOR2 tempSize;
	for ( int i = 0; i < SKILL_ID::SKILL_MAX; i++ )
	{
		//int tempType = SkillManager::GetPlayerType ( _num );
		//skillIcon[ tempType ][ i ].
		skillIcon[ i ].SetPosition ( _pos.x + 25 + ( 50 * ( float )i ), _pos.y + 85 );
		skillIcon[ i ].Draw ();

		tempSize = skillMask.GetDefaultSize ();
		tempSize.y *= SkillManager::GetCoolTime ( _num, ( SKILL_ID )i );
		skillMask.SetPosition ( _pos.x + 25 + ( 50 * ( float )i ), _pos.y + 85 );
		skillMask.SetSize ( tempSize );
		skillMask.Draw ();
	}
}