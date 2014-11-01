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

wchar_t* charcterIconName[ ] =
{
	L"Resource/Scene/CharacterSelect/CharacterSelect_Icon_1.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_Icon_2.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_Icon_3.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_Icon_4.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_Icon_Random.png"
};

D3DXVECTOR2 playerIconPos[] =
{
	D3DXVECTOR2 ( 50, 100 ),
	D3DXVECTOR2 ( 870, 100 ),
	D3DXVECTOR2 ( 50, 450 ),
	D3DXVECTOR2 ( 870, 450 ),
};

D3DXVECTOR2 charcterIconPos[ ] =
{
	D3DXVECTOR2 ( 525, 300 ),
	D3DXVECTOR2 ( 700, 300 ),
	D3DXVECTOR2 ( 525, 480 ),
	D3DXVECTOR2 ( 700, 480 ),
	D3DXVECTOR2 ( 610, 390 ),
};


SelectIcon::SelectIcon ()
{
	iconState = new SelectIcon::IconState[ 4 ];
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
		iconState[ i ].iconNum = 5;

		charSprite[ i ].Create ( playerIconName[ i ] );
		charSprite[ i ].SetPosition ( playerIconPos[ i ] );
	}

	for ( int i = 0; i < 5; i++ )
	{
		selectSprite[ i ].Create ( charcterIconName[ i ] );
		selectSprite[ i ].SetPosition ( charcterIconPos[ i ] );
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
			iconSprite.SetPosition ( playerIconPos[ i ]  );
			iconSprite.Draw ();
		}
	}

	for ( int i = 0; i < 5; i++ )
	{
		selectSprite[ i ].Draw ();
	}
}

void SelectIcon::ChangeIcon ( int _num, int _icon )
{
	iconState[ _num ].iconNum = _icon;
}

void SelectIcon::CursorCollision ()
{
}