#include "Object/Skill/YellowSkill.h"
#include "Object/Skill/Skill.h"
#include "Loader/PlayerLoader.h"

D3DXVECTOR2 yellowPosition[ 2 ][ 3 ] =
{
	{
		D3DXVECTOR2 ( 0, -290.0f ),
		D3DXVECTOR2 ( -100, -290.0f ),
		D3DXVECTOR2 ( -20, -400.0f )
	},
	{
		D3DXVECTOR2 ( -400, -290.0f ),
		D3DXVECTOR2 ( -1000, -290.0f ),
		D3DXVECTOR2 ( -820, -400.0f )
	},
};


YellowSkill::~YellowSkill ()
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

void YellowSkill::Init ()
{
	Skill* first = new Skill;
	first->Init ( "Resource/Object/Skill/Yellow/Yellow_Skill_First.bin", L"Resource/Object/Skill/Yellow/Yellow_Skill_First.png", SKILL_ID_LOAD::SKILL_ID_YELLOW );
	skills.push_back ( first );

	Skill* second = new Skill;
	second->Init ( "Resource/Object/Skill/Yellow/Yellow_Skill_Second.bin", L"Resource/Object/Skill/Yellow/Yellow_Skill_Second.png", SKILL_ID_LOAD::SKILL_ID_YELLOW );
	skills.push_back ( second );

	Skill* third = new Skill;
	third->Init ( "Resource/Object/Skill/Yellow/Yellow_Skill_Third.bin", L"Resource/Object/Skill/Yellow/Yellow_Skill_Third.png", SKILL_ID_LOAD::SKILL_ID_YELLOW );
	skills.push_back ( third );

	SkillSet::Initb2Body ();
}

void YellowSkill::Update ()
{
	for ( auto& skill : skills )
	{
		skill->Update ( body );
	}
}

void YellowSkill::Draw ()
{
	for ( auto& skill : skills )
		skill->Draw ();
}

void YellowSkill::SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg )
{
	SkillSetDettachFixture ( body );

	D3DXVECTOR2 temp = ( _pos * 32.0f );
	skills[ _id ]->SetPosition ( ( temp + yellowPosition[ dirFlg ][ _id ] ), dirFlg );
	skills[ _id ]->SkillOn ();
	temp = skills[ _id ]->GetPosition ();
	body->SetTransform ( b2Vec2 ( temp.x / 32.0f, temp.y / 32.0f ), 0 );
	skills[ _id ]->SetAttachFixture ( body );
}

b2Body* YellowSkill::Getb2Body ()
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