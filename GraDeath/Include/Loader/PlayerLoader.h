#ifndef _PLAYER_LOADER_H_
#define _PLAYER_LOADER_H_

#include "CharacterController/CharacterInfo.h"
#include "Object/ObjectParameter.h"


namespace PlayerLoader
{

	ObjectParameter LoadFile ( const char* _filename );

	char* GetLoadFileName ( CharacterInfo::PLAYER_TYPE _type );

};

#endif	// end of CharacterLoader