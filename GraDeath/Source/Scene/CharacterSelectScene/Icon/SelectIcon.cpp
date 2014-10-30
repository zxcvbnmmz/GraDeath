#include "Scene/CharacterSelectScene/Icon/SelectIcon.h"
#include "Utility/SafeDelete.h"


struct SelectIcon::IconState
{
	int iconNum;
};

wchar_t* playerIconName[ ] =
{
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_1.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_2.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_3.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_4.png"
};

D3DXVECTOR2 playerIconPos[] =
{
	D3DXVECTOR2 ( 10, 10 ),
	D3DXVECTOR2 ( 10, 10 ),
	D3DXVECTOR2 ( 10, 10 ),
	D3DXVECTOR2 ( 10, 10 )
};

SelectIcon::SelectIcon ()
{
	iconState = new SelectIcon::IconState[ 4 ];
	for ( int i = 0; i < 4; i++ )
		iconState[ i ].iconNum = 5;
}

SelectIcon::~SelectIcon ()
{
	Util::safeDeleteArray ( iconState );
}

void SelectIcon::SetUp ()
{
	iconSprite.Create ( L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_Non.png" );

	for ( int i = 0; i < 4; i++ )
	{
		charSprite[ i ].Create ( playerIconName[ i ] );
		charSprite[ i ].SetPosition ( D3DXVECTOR2( 0, 0 ) );
	}
}

void SelectIcon::Draw ()
{
	for ( int i = 0; i < 4; i++ )
	{
		if ( iconState[ i ].iconNum != 5 )
		{
			charSprite[ iconState[ i ].iconNum ].SetPosition ( playerIconPos[ iconState[ i ].iconNum ] );
			charSprite[ iconState[ i ].iconNum ].Draw ();
		}
		else
		{
			iconSprite.Draw ();
		}
	}
}

void SelectIcon::ChangeIcon ( int _num, int _icon )
{
	iconState[ _num ].iconNum = _icon;
}