#include "Object/Skill/WhiteBlackSecond.h"

WhiteBlackSecond::WhiteBlackSecond ()
{
}

WhiteBlackSecond::~WhiteBlackSecond ()
{
}


void WhiteBlackSecond::Init ( std::string _filename, std::wstring _path )
{
	skills[ 0 ].Init ( "Resource/Object/Skill/WhiteBlack/shirokuro_skill01.bin", L"Resource/Object/Skill/WhiteBlack/" );
	skills[ 1 ].Init ( "Resource/Object/Skill/WhiteBlack/shirokuro_skill01.bin", L"Resource/Object/Skill/WhiteBlack/" );
	skills[ 2 ].Init ( "Resource/Object/Skill/WhiteBlack/shirokuro_skill01.bin", L"Resource/Object/Skill/WhiteBlack/" );
}

void WhiteBlackSecond::Update ()
{
	skills[ 0 ].Update ();
	skills[ 1 ].Update ();
}

void WhiteBlackSecond::Draw ()
{
	skills[ 0 ].Draw ();
	skills[ 1 ].Draw ();
}

void WhiteBlackSecond::Move ()
{
	for ( int i = 0; i < WHITE_BLACK_SECOND_MAX; i++ )
	{
		D3DXVECTOR2 position = skills[ i ].GetPosition ();
	}
}

void WhiteBlackSecond::SetPosition ( const D3DXVECTOR2& _pos, unsigned int dirFlg )
{
	if ( dirFlg == 0 )
	{
		skills[ 0 ].SetPosition ( D3DXVECTOR2 ( _pos.x + 50, _pos.y ), 2 );
		skills[ 1 ].SetPosition ( D3DXVECTOR2 ( _pos.x + 1250, _pos.y ), 2 );
		skills[ 2 ].SetPosition ( D3DXVECTOR2 ( _pos.x + 650, _pos.y ), 2 );
	}
	else
	{
		skills[ 0 ].SetPosition ( D3DXVECTOR2 ( _pos.x - 1250, _pos.y ), 2 );
		skills[ 1 ].SetPosition ( D3DXVECTOR2 ( _pos.x - 50, _pos.y ), 2 );
		skills[ 2 ].SetPosition ( D3DXVECTOR2 ( _pos.x - 650, _pos.y ), 2 );
	}
}

AnimationData& WhiteBlackSecond::GetAnimationData ()
{
	return skills[ 0 ].GetAnimationData ();
}