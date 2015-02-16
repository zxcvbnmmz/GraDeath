#ifndef _PLAYER_LOADER_H_
#define _PLAYER_LOADER_H_

#include "CharacterController/CharacterInfo.h"

struct AnimationData;


enum SKILL_ID_LOAD
{
	SKILL_ID_RED = 0,
	SKILL_ID_BLUE,
	SKILL_ID_YELLOW,
	SKILL_ID_BLACKWHITE,
	SKILL_ID_MAX
};
/*
PLAYER_RED = 0,
PLAYER_BLUE,
PLAYER_YELLOW,
PLAYER_GRAY,
*/
namespace PlayerLoader
{

	void LoadFile ( const int _num, AnimationData* parameter );

	void LoadFile ( const char* filename, AnimationData* parameter, int skill_id );

	//char* GetLoadFileName ( CharacterInfo::PLAYER_TYPE _type );

};

#endif	// end of CharacterLoader