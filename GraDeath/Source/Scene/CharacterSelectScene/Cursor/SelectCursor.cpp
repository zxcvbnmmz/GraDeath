#include "Scene/CharacterSelectScene/Cursor/SelectCursor.h"
#include "Utility/SafeDelete.h"
#include "Input/GamePad.h"
#include "D2D/Sprite/Sprite.h"

#define MOVE_SPEED ( 2.0F )

struct CursorState
{
	Sprite			cursor;
	D3DXVECTOR2		pos;
	bool			active;
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
	GamePad::setThreshold ( 0.3f );
}

SelectCursor::~SelectCursor ()
{
	Util::safeDeleteArray ( cursorState );
}

void SelectCursor::SetUp ()
{
	for ( int i = 0; i < 4; i++ )
	{
		cursorState[ i ].pos = cursorPos[ i ];
		cursorState[ i ].cursor.Create ( cursorName );
		cursorState[ i ].cursor.SetPosition ( cursorState[ i ].pos );
		cursorState[ i ].active = false;
	}
	cursorState[ 0 ].active = true;
}

void SelectCursor::Update ()
{
	float angle[ 4 ] = { 0 };
	for ( int i = 0; i < 4; i++ )
	{
		if ( GamePad::getLStickState ( ( PAD_NUM )i, angle[ i ] ) )
		{
			cursorState[ i ].pos.x -= cos ( angle[ i ] ) * MOVE_SPEED;
			cursorState[ i ].pos.y += sin ( angle[ i ] ) * MOVE_SPEED;
		}
	}
}

void SelectCursor::Draw ()
{
	for ( int i = 0; i < 4; i++ )
	{
		if ( cursorState[ i ].active )
		{
			cursorState[ i ].cursor.SetPosition ( cursorState[ i ].pos );
			cursorState[ i ].cursor.Draw ();
		}
	}
}

D3DXVECTOR2& SelectCursor::GetPadCursorPositon ( int num )
{
	return cursorState[ num ].pos;
}