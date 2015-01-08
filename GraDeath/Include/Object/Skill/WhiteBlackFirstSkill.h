#ifndef _WHITE_BLACK_FIRST_SKILL_H_
#define _WHITE_BLACK_FIRST_SKILL_H_

#include "Object/Skill/Skill.h"


class WhiteBlackFirstSkill : public Skill
{
public:
	WhiteBlackFirstSkill ();

	~WhiteBlackFirstSkill ();

	void SetPosition ( const D3DXVECTOR2& _pos );

	AnimationData& GetAnimationData ();
};


#endif