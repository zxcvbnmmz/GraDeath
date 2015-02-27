#include "Object/Skill/YellowSkill.h"
#include "Object/Skill/Skill.h"
#include "Loader/PlayerLoader.h"

D3DXVECTOR2 yellowPosition[ 2 ][ 3 ] =
{
	{
		D3DXVECTOR2 ( 75, -210.0f ),
		D3DXVECTOR2 ( -340, -360.0f ),
		D3DXVECTOR2 ( -350, -350.0f )
	},
	{
		D3DXVECTOR2 ( -400, -210.0f ),
		D3DXVECTOR2 ( -340, -360.0f ),
		D3DXVECTOR2 ( -350, -350.0f )
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

bool YellowSkill::SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg )
{
	if ( _id >= skills.size () )
		return false;

	for ( auto& skill : skills )
	{
		if ( skill->IsActive () )
		{
			return false;
		}
	}
	SkillSetDettachFixture ( body );

	D3DXVECTOR2 temp = ( _pos * 32.0f );
	skills[ _id ]->SetPosition ( ( temp + yellowPosition[ dirFlg ][ _id ] ), dirFlg );
	skills[ _id ]->SkillOn ();
	temp = skills[ _id ]->GetPosition ();
	body->SetTransform ( b2Vec2 ( temp.x / 32.0f, temp.y / 32.0f ), 0 );
	skills[ _id ]->SetAttachFixture ( body );

	return true;
}

bool YellowSkill::IsActive ()
{
	for ( auto& skill : skills )
	{
		if ( skill->IsActive () )
		{
			return true;
		}
	}
	return false;
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