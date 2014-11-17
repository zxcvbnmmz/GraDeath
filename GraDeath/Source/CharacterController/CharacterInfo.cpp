#include "CharacterController/CharacterInfo.h"


namespace CharacterInfoFunc
{
	namespace
	{
		static const int playerNum = 4;
		CharacterInfo info[ playerNum ];
	}

	void SetCharacterInfo ( CharacterInfo* _info )
	{
		for ( int i = 0; i < playerNum; i++ )
		{
			info[ i ] = _info[ i ];
		}
	}

	CharacterInfo* GetCharacterInfo ()
	{
		return info;
	}
}