#ifndef _PLAYER_LOADER_H_
#define _PLAYER_LOADER_H_

#include "CharacterController/CharacterInfo.h"


struct ObjectParameter;

namespace PlayerLoader
{

	void LoadFile ( const char* _filename, ObjectParameter& parameter );

	char* GetLoadFileName ( CharacterInfo::PLAYER_TYPE _type );

};

#endif	// end of CharacterLoader