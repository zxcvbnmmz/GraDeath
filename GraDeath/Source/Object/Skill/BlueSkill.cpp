#include "Object/Skill/BlueSkill.h"
#include "Object/Skill/Skill.h"
#include "Loader/PlayerLoader.h"

D3DXVECTOR2 bluePosition[ 2 ][ 3 ] =
{
	{
		D3DXVECTOR2 ( 200, -215.0f ),
		D3DXVECTOR2 ( -380, -350.0f ),
		D3DXVECTOR2 ( -20, -400.0f )
	},
	{
		D3DXVECTOR2 ( -380, -215.0f ),
		D3DXVECTOR2 ( -400, -350.0f ),
		D3DXVECTOR2 ( -820, -400.0f )
	},
};



BlueSkill::~BlueSkill ()
{
	int size = skills.size ();
	for ( int i = 0; i < size; i++ )
	{
		if ( skills[ i ] != nullptr )
		{
			delete skills[ i ];
			skills[ i ] = nullptr;
		}
	}
	skills.clear ();

	World::DestoryBody ( body );
}

void BlueSkill::Init ()
{
	Skill* first = new Skill;
	first->Init ( "Resource/Object/Skill/Blue/Blue_Skill_First.bin", L"Resource/Object/Skill/Blue/Blue_Skill_First.png", SKILL_ID_LOAD::SKILL_ID_BLUE );
	skills.push_back ( first );

	//WhiteBlackSecond* second = new WhiteBlackSecond;
	//second->Init ( "", L"" );
	//skills.push_back ( second );

	Skill* third = new Skill;
	third->Init ( "Resource/Object/Skill/Blue/Blue_Skill_Third3.bin", L"Resource/Object/Skill/Blue/Blue_Skill_Third3.png", SKILL_ID_LOAD::SKILL_ID_BLUE );
	//third->SetSize ( D3DXVECTOR2 ( 600, 600 ));
	skills.push_back ( third );

	SkillSet::Initb2Body ();
}

void BlueSkill::Update ()
{
	for ( auto& skill : skills )
	{
		skill->Update ( body );
	}
}

void BlueSkill::Draw ()
{
	for ( auto& skill : skills )
		skill->Draw ();
}

void BlueSkill::SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg )
{
	if ( _id >= skills.size () )
		return;

	SkillSetDettachFixture ( body );

	D3DXVECTOR2 temp = ( _pos * 32.0f );
	skills[ _id ]->SetPosition ( ( temp + bluePosition[ dirFlg ][ _id ] ), dirFlg );
	skills[ _id ]->SkillOn ();
	temp = skills[ _id ]->GetPosition ();
	body->SetTransform ( b2Vec2 ( temp.x / 32.0f, temp.y / 32.0f ), 0 );
	skills[ _id ]->SetAttachFixture ( body );
}

b2Body* BlueSkill::Getb2Body()
{
	for ( auto& skill : skills )
	{
		if ( skill->IsActive () )
		{
			//skill->SetAttachFixture ( body );
			return body;
		}
	}
	return nullptr;// skills[ _num ]->Getb2Body ();
}