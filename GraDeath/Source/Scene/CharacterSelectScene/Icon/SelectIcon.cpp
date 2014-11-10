#include "Scene/CharacterSelectScene/Icon/SelectIcon.h"
#include "Utility/SafeDelete.h"


struct SelectIcon::IconState
{
	int iconNum;
	CharacterInfo info;
};

wchar_t* playerIconName[ ] =
{
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_1.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_2.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_3.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_4.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_Random.png"
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
	D3DXVECTOR2 ( 0, 0 ),
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
		info[ i ].pType = CharacterInfo::PLAYER_TYPE::PLAYER_NON;
		info[ i ].pcType = CharacterInfo::PC_TYPE::PC_NON;

		iconState[ i ].iconNum = 5;
		iconState[ i ].info.pType = CharacterInfo::PLAYER_TYPE::PLAYER_NON;
		iconState[ i ].info.pcType = CharacterInfo::PC_TYPE::PC_NON;
	}

	for ( int i = 0; i < 5; i++ )
	{
		charSprite[ i ].Create ( playerIconName[ i ] );
		charSprite[ i ].SetPosition ( playerIconPos[ i ] );

		selectSprite[ i ].Create ( charcterIconName[ i ] );
		selectSprite[ i ].SetPosition ( charcterIconPos[ i ] );
	}
}

void SelectIcon::Draw ()
{
	for ( int i = 0; i < 4; i++ )
	{
		int iconNum = iconState[ i ].iconNum;
		if ( iconNum == 5 )
		{
			iconSprite.SetPosition ( playerIconPos[ i ] );
			iconSprite.Draw ();
		}
		else
		{
			charSprite[ iconNum ].SetPosition ( playerIconPos[ i ] );
			charSprite[ iconNum ].Draw ();
		}
	}

	for ( int i = 0; i < 5; i++ )
		selectSprite[ i ].Draw ();
}

void SelectIcon::CursorCollision ( int num, D3DXVECTOR2& _pos )
{
	for ( int i = 0; i < 5; i++ )
	{
		iconState[ num ].iconNum = 5;
		D3DXVECTOR2 pos = selectSprite[ i ].GetPosition ();
		D3DXVECTOR2 size = selectSprite[ i ].GetDefaultSize ();
		if ( _pos.x < pos.x + size.x &&
			_pos.x > pos.x &&
			_pos.y <  pos.y + size.y &&
			_pos.y >  pos.y )
		{
			iconState[ num ].iconNum = i;
			iconState[ num ].info.pType = ( CharacterInfo::PLAYER_TYPE )i;
			break;
		}
	} 
}

CharacterInfo SelectIcon::GetCharacterInfo ( int _num )
{
	return iconState[ _num ].info;
}