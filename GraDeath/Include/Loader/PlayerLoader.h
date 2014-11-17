#ifndef _PLAYER_LOADER_H_
#define _PLAYER_LOADER_H_

#include "CharacterController/CharacterInfo.h"

struct AnimationData;

namespace PlayerLoader
{

	void LoadFile ( const char* _filename, AnimationData* parameter );

	char* GetLoadFileName ( CharacterInfo::PLAYER_TYPE _type );

};

#endif	// end of CharacterLoader