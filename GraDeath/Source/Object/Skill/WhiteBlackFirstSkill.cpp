#include "Object/Skill/WhiteBlackFirstSkill.h"


WhiteBlackFirstSkill::WhiteBlackFirstSkill ()
{
}

WhiteBlackFirstSkill::~WhiteBlackFirstSkill ()
{
}

void WhiteBlackFirstSkill::SetPosition ( const D3DXVECTOR2& _pos )
{
	pos = _pos;
}

AnimationData& WhiteBlackFirstSkill::GetAnimationData ()
{
	return animSkill;
}