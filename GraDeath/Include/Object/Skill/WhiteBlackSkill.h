#ifndef _WHITE_BLACK_SKILL_H_
#define _WHITE_BLACK_SKILL_H_

#include "Object/Skill/SkillSet.h"

class WhiteBlackSkill : public SkillSet
{
public:
	WhiteBlackSkill (){}

	~WhiteBlackSkill ();

	void Init ();

	void Update ();

	virtual void Draw ();

	virtual bool SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg );

	bool IsActive ();

	b2Body* Getb2Body ();

};

#endif