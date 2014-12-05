#ifndef _SKIL_MANAGER_H_
#define _SKIL_MANAGER_H_

#include "Object/SkillDefine.h"

namespace SkillManager
{
	void SetSkill ( int _num );

	void Update ();

	bool SkillUse ( int _num, SKILL_ID _id );

}

#endif