#include "Object/Skill/WhiteBlackSecond.h"

WhiteBlackSecond::WhiteBlackSecond ()
{
}

WhiteBlackSecond::~WhiteBlackSecond ()
{
}


void WhiteBlackSecond::Init ( std::string _filename, std::wstring _path )
{
	skills[ 0 ].Init ( "Resource/Object/Skill/WhiteBlack/shiro.bin", L"Resource/Object/Skill/WhiteBlack/shiro.png" );
	skills[ 1 ].Init ( "Resource/Object/Skill/WhiteBlack/kuro.bin", L"Resource/Object/Skill/WhiteBlack/kuro.png" );
	skills[ 2 ].Init ( "Resource/Object/Skill/WhiteBlack/explo.bin", L"Resource/Object/Skill/WhiteBlack/explo.png" );
}

void WhiteBlackSecond::Update ()
{
	if ( !skillFlg )
		return;

	if ( Flag )
	{
		skills[ 0 ].Update ();
		skills[ 1 ].Update ();
		Move ();
	}
}

void WhiteBlackSecond::Draw ()
{
	if ( !skillFlg )
		return;

	skills[ 0 ].Draw ();
	skills[ 1 ].Draw ();
}

void WhiteBlackSecond::Move ()
{
	D3DXVECTOR2 position = skills[ 0 ].GetPosition ();
	position.x += 2;
	skills[ 0 ].SetPosition ( position, 0 );

	position = skills[ 1 ].GetPosition ();
	position.x += 2;
	skills[ 1 ].SetPosition ( position, 0 );

	dir += 2;
	if ( dir >= 300.0f )
	{
		skillFlg = Flag = false;
		dir = .0f;
		skills[ 0 ].SkillOff ();
		skills[ 1 ].SkillOff ();
	}
}

void WhiteBlackSecond::SetPosition ( const D3DXVECTOR2& _pos, unsigned int dirFlg )
{
	if ( dirFlg == 0 )
	{
		skills[ 0 ].SetPosition ( D3DXVECTOR2 ( _pos.x + 50, _pos.y ), 0 );
		skills[ 1 ].SetPosition ( D3DXVECTOR2 ( _pos.x + 1250, _pos.y ), 0 );
		skills[ 2 ].SetPosition ( D3DXVECTOR2 ( _pos.x + 650, _pos.y ), 0 );

	}
	else
	{
		skills[ 0 ].SetPosition ( D3DXVECTOR2 ( _pos.x - 1250, _pos.y ), 0 );
		skills[ 1 ].SetPosition ( D3DXVECTOR2 ( _pos.x - 50, _pos.y ), 0 );
		skills[ 2 ].SetPosition ( D3DXVECTOR2 ( _pos.x - 650, _pos.y ), 0 );
	}
	skills[ 0 ].SkillOn ();
	skills[ 1 ].SkillOn ();
	Flag = true;
}

AnimationData& WhiteBlackSecond::GetAnimationData ()
{
	return skills[ 0 ].GetAnimationData ();
}