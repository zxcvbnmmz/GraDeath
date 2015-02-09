#include "Scene/CharacterSelectScene/Cursor/SelectCursor.h"
#include "Scene/CharacterSelectScene/Icon/SelectIcon.h"
#include "Utility/SafeDelete.h"
#include "Input/GamePad.h"


#define MOVE_SPEED ( 15.0F )

struct CursorState
{
	D3DXVECTOR2		pos;
	bool			active;
	bool			selectFlg;
	int				selectChara;
	Sprite			icon;
};

wchar_t* cursorName = L"Resource/Scene/CharacterSelect/Cursor.png";

D3DXVECTOR2 cursorPos[ ] =
{
	D3DXVECTOR2 ( 100, 100 ),
	D3DXVECTOR2 ( 100, 100 ),
	D3DXVECTOR2 ( 100, 100 ),
	D3DXVECTOR2 ( 100, 100 ),
};

SelectCursor::SelectCursor ()
{
	cursorState = new CursorState[ 4 ];
	GamePad::setThreshold ( 0.4f );
	icon = std::shared_ptr<SelectIcon> ( new SelectIcon );
}

SelectCursor::~SelectCursor ()
{
	Util::safeDeleteArray ( cursorState );
}

// 初期化
void SelectCursor::SetUp ()
{
	for ( int i = 0; i < 4; i++ )
	{
		cursorState[ i ].pos = cursorPos[ i ];
		cursorState[ i ].active = false;
		cursorState[ i ].selectFlg = false;
		cursorState[ i ].icon.Create ( cursorName );
		cursorState[ i ].icon.SetPosition ( cursorPos[ i ] );
	}
	cursorState[ 0 ].active = true;

	icon->SetUp ();
}

// 更新
void SelectCursor::Update ()
{
	float angle[ 4 ] = { 0 };
	for ( int i = 0; i < 4; i++ )
	{
		SubUpdate ( i );
		if ( cursorState[ i ].active )
			icon->CursorCollision ( i, cursorState[ i ].pos );
	}
}

// 描画
void SelectCursor::Draw ()
{
	icon->Draw ();
	for ( int i = 0; i < 4; i++ )
	{
		if ( cursorState[ i ].active && !cursorState[ i ].selectFlg )
		{
			cursorState[ i ].icon.SetPosition ( cursorState[ i ].pos );
			cursorState[ i ].icon.Draw ();
		}
	}
}

bool SelectCursor::AllSelectCheck ()
{
	for ( int i = 0; i < 4; i++ )
	{
		if ( cursorState[ i ].active &&
			!cursorState[ i ].selectFlg )
		{
			return false;
		}
	}
	return true;
}

CharacterInfo SelectCursor::GetCharacterInfo ( int _num )
{
	return icon->GetCharacterInfo ( _num );
}


// サブ更新
void SelectCursor::SubUpdate ( int _num )
{
	PAD_NUM padID = ( PAD_NUM )_num;

	if ( !cursorState[ _num ].active )
	{
		if ( INPUT_STATE::INPUT_PUSH == GamePad::getGamePadState ( padID, BUTTON_ID::BUTTON_START ) )
			cursorState[ _num ].active = true;
		else
			return;
	}

	Move ( _num );
	Determination ( _num );
}

void SelectCursor::Move ( int _num )
{
	PAD_NUM padID = ( PAD_NUM )_num;

	float angle = .0f;
	if ( GamePad::getLStickState ( padID, angle ) )
	{
		cursorState[ _num ].pos.x += cos ( angle ) * MOVE_SPEED;
		cursorState[ _num ].pos.y -= sin ( angle ) * MOVE_SPEED;
	}
}

void SelectCursor::Determination ( int _num )
{
	PAD_NUM padID = ( PAD_NUM )_num;

	if ( INPUT_STATE::INPUT_PUSH == GamePad::getGamePadState ( padID, BUTTON_ID::BUTTON_A ) &&
		icon->GetCharacterInfo( _num ).pType != CharacterInfo::PLAYER_TYPE::PLAYER_NON )
	{
		cursorState[ _num ].selectFlg = true;
	}
}