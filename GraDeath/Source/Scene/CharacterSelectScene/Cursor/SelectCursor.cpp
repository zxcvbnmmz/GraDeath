#include "Scene/CharacterSelectScene/Cursor/SelectCursor.h"
#include "Scene/CharacterSelectScene/Icon/SelectIcon.h"
#include "Utility/SafeDelete.h"
#include "Input/GamePad.h"
#include "Input/Keyboard.h"
#include "System/Window.h"
#include "Sound/Sound.h"
#include <stdlib.h>

#ifdef _DEBUG
#include "D2D/Brush/SolidBrush.h"
#endif

#define MOVE_SPEED ( 20.0F )

struct CursorState
{
	D3DXVECTOR2		pos;
	bool			active;
	bool			selectFlg;
	int				selectChara;
	Sprite			icon;
};

wchar_t* cursorName[] =
{
	L"Resource/Scene/CharacterSelect/Cursor.png",
	L"Resource/Scene/CharacterSelect/Cursor2.png",
	L"Resource/Scene/CharacterSelect/Cursor3.png",
	L"Resource/Scene/CharacterSelect/Cursor4.png",
};

D3DXVECTOR2 cursorPos[ ] =
{
	D3DXVECTOR2 ( 100, 100 ),
	D3DXVECTOR2 ( 100, 450 ),
	D3DXVECTOR2 ( 1200, 100 ),
	D3DXVECTOR2 ( 1200, 450 ),
};

SelectCursor::SelectCursor ()
{
	cursorState = new CursorState[ 4 ];
	GamePad::setThreshold ( 0.4f );
	icon = std::shared_ptr<SelectIcon> ( new SelectIcon );

	System::Window::GetWindowSize ( &maxWidth, &maxHeight );

	seVoiceList[ 0 ] = Sound::CreateSE ( "Resource/Voice/chara1_select.wav" );
	seVoiceList[ 1 ] = Sound::CreateSE ( "Resource/Voice/chara2_select.wav" );
	seVoiceList[ 2 ] = Sound::CreateSE ( "Resource/Voice/chara3_select.wav" );
	seVoiceList[ 3 ] = Sound::CreateSE ( "Resource/Voice/chara4_select.wav" );

#ifdef _DEBUG
	temp.format = D2D::TextFormat::Create ( L"MS明朝", 30 );
	temp.brush = SolidBrush::Create ( 1, 1, 1, 1 );
#endif
}

SelectCursor::~SelectCursor ()
{
	Util::safeDeleteArray ( cursorState );

	for ( int i = 0; i < 4; ++i ){
		if ( seVoiceList[ i ] != nullptr )
			seVoiceList[ i ]->Release ();
	}
}

// 初期化
void SelectCursor::SetUp ()
{
	for ( int i = 0; i < 4; i++ )
	{
		cursorState[ i ].pos = cursorPos[ i ];
#ifdef _DEBUG
		cursorState[ i ].active = false;
#else
		cursorState[ i ].active = true;
#endif
		cursorState[ i ].selectFlg = false;
		cursorState[ i ].selectChara = 4;
		cursorState[ i ].icon.Create ( cursorName[i] );
		cursorState[ i ].icon.SetPosition ( cursorPos[ i ] );
	}
#ifdef _DEBUG
	cursorState[ 0 ].active = true;
#endif
	icon->SetUp ();
}

// 更新
void SelectCursor::Update ()
{
	float angle[ 4 ] = { 0 };
	for ( int i = 0; i < 4; i++ )
	{
		SubUpdate ( i );

		if ( cursorState[ i ].active && !cursorState[ i ].selectFlg )
			icon->CursorCollision ( i, cursorState[ i ].pos );
	}
#ifdef _DEBUG
	if ( Keyboard::CheckKey ( KC_RIGHT ) == INPUT_PUSH )
		tempCharNum = ( tempCharNum + 1 ) % 4;
	if ( Keyboard::CheckKey ( KC_LEFT ) == INPUT_PUSH )
		tempCharNum = ( tempCharNum + 3 ) % 4;
#endif
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
#ifdef _DEBUG
	temp.DrawString ( 600, 0, L"SelectNum ←→で番号切り替え %d", tempCharNum );
#endif
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
#ifdef _DEBUG
	if ( _num == 0 )
	{
		//CharacterInfo tempInfo;
		//tempInfo.pType = ( CharacterInfo::PLAYER_TYPE ) tempCharNum ;
		//tempInfo.pcType = CharacterInfo::PC_TYPE::PC_PLAYER;
		//return tempInfo;
	}
#endif
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

	if ( cursorState[ _num ].selectFlg )
		return;

	float angle = .0f;
	if ( GamePad::getLStickState ( padID, angle ) )
	{
		cursorState[ _num ].pos.x += cos ( angle ) * MOVE_SPEED;
		cursorState[ _num ].pos.y -= sin ( angle ) * MOVE_SPEED;
	}

	if ( ( cursorState[ _num ].pos.x + 25.0f ) >= maxWidth )
		cursorState[ _num ].pos.x = maxWidth - 25.0f;
	if ( cursorState[ _num ].pos.x <= 0 )
		cursorState[ _num ].pos.x = 0;
	if ( cursorState[ _num ].pos.y + 25.0f >= maxHeight )
		cursorState[ _num ].pos.y = maxHeight - 25.0f;
	if ( cursorState[ _num ].pos.y <= 0 )
		cursorState[ _num ].pos.y = 0;
}

void SelectCursor::Determination ( int _num )
{
	PAD_NUM padID = ( PAD_NUM )_num;

	if ( INPUT_STATE::INPUT_PUSH == GamePad::getGamePadState ( padID, BUTTON_ID::BUTTON_A ) &&
		icon->GetCharacterInfo( _num ).pType != CharacterInfo::PLAYER_TYPE::PLAYER_NON )
	{
		if ( icon->GetCharacterInfo ( _num ).pType == CharacterInfo::PLAYER_TYPE::PLAYER_RONDOM )
		{
			icon->SetRandomChar ( _num, ( CharacterInfo::PLAYER_TYPE )(rand() % 4) );
		}
		seVoiceList[ icon->GetCharacterInfo ( _num ).pType ]->Stop ();
		seVoiceList[ icon->GetCharacterInfo ( _num ).pType ]->Play ();
		cursorState[ _num ].selectFlg = true;
	}
}