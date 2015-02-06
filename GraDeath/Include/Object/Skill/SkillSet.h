#ifndef _SKILL_SET_H_
#define _SKILL_SET_H_

#include <vector>

class Skill;
struct AnimationData;
struct D3DXVECTOR2;
class b2Body;

class SkillSet
{
protected:
	std::vector< Skill* > skills;

public:
	SkillSet (){}

	virtual ~SkillSet (){}

	virtual void Init () = 0;

	virtual void Update () = 0;

	virtual void Draw () = 0;

	virtual void SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg ) = 0;

	virtual b2Body& Getb2Body ( int _num ) = 0;

};
#endif
