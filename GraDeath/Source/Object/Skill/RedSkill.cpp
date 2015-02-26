#include "Object/Skill/RedSkill.h"
#include "Object/Skill/Skill.h"
#include "Loader/PlayerLoader.h"

D3DXVECTOR2 redPosition[ 2 ][ 3 ] =
{
	{
		D3DXVECTOR2 ( 100, -212.0f ),
		D3DXVECTOR2 ( 200, -365.0f ),
		D3DXVECTOR2 ( -200, -350.0f )
	},
	{
		D3DXVECTOR2 ( -350, -212.0f ),
		D3DXVECTOR2 ( -900, -365.0f ),
		D3DXVECTOR2 ( -450, -350.0f )
	},
};


RedSkill::~RedSkill ()
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

void RedSkill::Init ()
{
	Skill* first = new Skill;
	first->Init ( "Resource/Object/Skill/Red/Red_Skill_First.bin", L"Resource/Object/Skill/Red/Red_Skill_First.png", SKILL_ID_LOAD::SKILL_ID_RED );
	skills.push_back ( first );

	Skill* second = new Skill;
	second->Init ( "Resource/Object/Skill/Red/Red_Skill_Third.bin", L"Resource/Object/Skill/Red/Red_Skill_Third.png", SKILL_ID_LOAD::SKILL_ID_RED );
	skills.push_back ( second );

	Skill* third = new Skill;
	third->Init ( "Resource/Object/Skill/Red/Red_Skill_SP.bin", L"Resource/Object/Skill/Red/Red_Skill_SP.png", SKILL_ID_LOAD::SKILL_ID_RED );
	//third->SetSize ( D3DXVECTOR2 ( 600, 600 ));
	skills.push_back ( third );

	SkillSet::Initb2Body ();
}

void RedSkill::Update ()
{
	for ( auto& skill : skills )
	{
		skill->Update ( body );
	}
}

void RedSkill::Draw ()
{
	for ( auto& skill : skills )
		skill->Draw ();
}

void RedSkill::SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg )
{
	if ( _id >= skills.size () )
		return

	SkillSetDettachFixture ( body );

	D3DXVECTOR2 temp = ( _pos * 32.0f );
	skills[ _id ]->SetPosition ( ( temp + redPosition[ dirFlg ][ _id ] ), dirFlg );
	skills[ _id ]->SkillOn ();
	temp = skills[ _id ]->GetPosition ();
	body->SetTransform ( b2Vec2 ( temp.x / 32.0f, temp.y / 32.0f ), 0 );
	skills[ _id ]->SetAttachFixture ( body );
}

b2Body* RedSkill::Getb2Body ()
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