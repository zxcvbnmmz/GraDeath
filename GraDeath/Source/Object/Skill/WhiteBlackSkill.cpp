#include "Object/Skill/WhiteBlackSkill.h"
#include "Object/Skill/WhiteBlackFirstSkill.h"

D3DXVECTOR2 setPosition[] =
{
	D3DXVECTOR2 ( 0, -290.0f ),
	D3DXVECTOR2 ( 0, 0 ),
	D3DXVECTOR2 ( 0, 0 )
};


WhiteBlackSkill::~WhiteBlackSkill ()
{
	int size = skills.size ();
	for ( int i = 0; i < size; i++ )
	{
		if ( skills[i] != nullptr )
		{
			delete skills[i];
			skills[i] = nullptr;
		}
	}
	skills.clear ();
}

void WhiteBlackSkill::Init ()
{
	Skill* first = new Skill;
	first->Init ( "Resource/Object/Skill/WhiteBlack/shirokuro_skill01.bin", L"Resource/Object/Skill/WhiteBlack/" );
	skills.push_back ( first );
}

void WhiteBlackSkill::Update ()
{
	for ( auto& skill : skills )
		skill->Update ();
}

void WhiteBlackSkill::Draw ()
{
	for ( auto& skill : skills )
		skill->Draw ();
}

void WhiteBlackSkill::SetPosition ( int _id, const D3DXVECTOR2 _pos )
{
	D3DXVECTOR2 temp = ( _pos * 32.0f );
	skills[ _id ]->SetPosition ( temp + setPosition[ _id ] );
	skills[ _id ]->SkillOn ();
}

AnimationData& WhiteBlackSkill::GetAnimationData ( int _num )
{
	return skills[ _num ]->GetAnimationData ();
}