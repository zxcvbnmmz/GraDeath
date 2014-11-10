#include "Scene/CharacterSelectScene/Cursor/SelectCursor.h"
#include "Utility/SafeDelete.h"
#include "Input/GamePad.h"


#define MOVE_SPEED ( 5.0F )

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
		cursorState[ i ].icon.Create ( cursorName );
		cursorState[ i ].icon.SetPosition ( cursorPos[ i ] );
	}
	cursorState[ 0 ].active = true;
	
}

// 更新
void SelectCursor::Update ()
{
	float angle[ 4 ] = { 0 };
	for ( int i = 0; i < 4; i++ )
		SubUpdate ( i );
}

// 描画
void SelectCursor::Draw ()
{
	for ( int i = 0; i < 4; i++ )
	{
		if ( cursorState[ i ].active )
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

// 各カーソルの位置取得
bool SelectCursor::GetPadCursorPositon ( int num, D3DXVECTOR2& _pos )
{
	if ( cursorState[ num ].active )
	{
		_pos = cursorState[ num ].pos;
		return true;
	}
	return false;
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

	float angle = .0f;
	if ( GamePad::getLStickState ( padID, angle ) )
	{
		cursorState[ _num ].pos.x += cos ( angle ) * MOVE_SPEED;
		cursorState[ _num ].pos.y -= sin ( angle) * MOVE_SPEED;
	}
}