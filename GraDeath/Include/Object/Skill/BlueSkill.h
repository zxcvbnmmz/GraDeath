#ifndef _BLUE_SKILL_H_
#define _BLUE_SKILL_H_

#include "Object/Skill/SkillSet.h"

struct D3DXVECTOR2;

class BlueSkill : public SkillSet
{
public:
	BlueSkill (){}

	~BlueSkill ();

	void Init ();

	void Update ();

	void Draw ();

	void SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg );

	AnimationData& GetAnimationData ( int _num );

};

#endif