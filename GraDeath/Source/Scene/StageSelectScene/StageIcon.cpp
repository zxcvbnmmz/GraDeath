#include "Scene/StageSelectScene/StageIcon.h"
#include "Utility/SafeDelete.h"
#include "Input/GamePad.h"


wchar_t* stageIconName[ ] =
{
	L"Resource/Scene/StageSelect/StageIcon_1.png",
	L"Resource/Scene/StageSelect/StageIcon_2.png",
	L"Resource/Scene/StageSelect/StageIcon_3.png",
	L"Resource/Scene/StageSelect/StageIcon_4.png",
	L"Resource/Scene/StageSelect/StageIcon_5.png",
	L"Resource/Scene/StageSelect/StageIcon_6.png"
};

D3DXVECTOR2 stageIconPos[ ] =
{
	D3DXVECTOR2 ( 50, 100 ),
	D3DXVECTOR2 ( 500, 100 ),
	D3DXVECTOR2 ( 950, 100 ),
	D3DXVECTOR2 ( 50, 400 ),
	D3DXVECTOR2 ( 500, 400 ),
	D3DXVECTOR2 ( 950, 400 ),
};

StageIcon::StageIcon ()
{
	selectSprite.Create ( L"Resource/Scene/StageSelect/StageIcon_Cursor.png" );
}

StageIcon::~StageIcon (){}

void StageIcon::SetUp ()
{
	for ( int i = 0; i < 6; i++ )
	{
		iconSprite[ i ].Create ( stageIconName[ i ] );
		iconSprite[ i ].SetPosition ( stageIconPos[ i ] );
	}
}

void StageIcon::Update ()
{
	CursorMovw ();
}

void StageIcon::Draw ()
{
	for ( int i = 0; i < 6; i++ )
	{
		iconSprite[ i ].Draw ();
	}
	selectSprite.SetPosition ( stageIconPos[ stageNum ] );
	selectSprite.Draw ();
}

int StageIcon::GetStageNum ()
{
	return stageNum;
}

void StageIcon::CursorMovw ()
{
	if ( INPUT_STATE::INPUT_PUSH == GamePad::getGamePadState ( PAD_1, BUTTON_RIGTH ) )
	{
		stageNum = ( stageNum + 1 ) % 6;
	}
	if ( INPUT_STATE::INPUT_PUSH == GamePad::getGamePadState ( PAD_1, BUTTON_LEFT ) )
	{
		stageNum = ( stageNum + 5 ) % 6;
	}
	if ( INPUT_STATE::INPUT_PUSH == GamePad::getGamePadState ( PAD_1, BUTTON_UP ) ||
		INPUT_STATE::INPUT_PUSH == GamePad::getGamePadState ( PAD_1, BUTTON_DOWN ) )
	{
		stageNum = ( stageNum + 3 ) % 6;
	}
}