#include "Object/Skill.h"
#include "Loader/PlayerLoader.h"
#include "Object/ObjectParameter.h"

void Skill::Init ( wchar_t* _filename )
{
	animSkill = std::shared_ptr< AnimationData > ( new AnimationData );
	//PlayerLoader::LoadFile ();
}

void Skill::Update ()
{

}

void Skill::Draw ()
{

}

void Skill::SetPosition ( const D3DXVECTOR2& _pos )
{

}