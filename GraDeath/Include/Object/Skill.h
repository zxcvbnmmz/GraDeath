#ifndef _SKILL_H_
#define _SKILL_H_

#include "Object/SkillDefine.h"
#include "CharacterController/CharacterInfo.h"
#include <memory>

class Sprite;
struct D3DXVECTOR2;
struct AnimationData;

class Skill
{
private:
	Sprite* skillAnim;
	std::shared_ptr< AnimationData > animSkill;

public:
	Skill (){}

	~Skill (){}

	void Init ( wchar_t* _filename );

	void Update ();

	void Draw ();

	void SetPosition ( const D3DXVECTOR2& _pos );

};

#endif