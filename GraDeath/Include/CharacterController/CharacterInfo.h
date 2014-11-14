#ifndef _CHARACTER_INFO_H_
#define _CHARACTER_INFO_H_


struct CharacterInfo
{
	enum PLAYER_TYPE
	{
		PLAYER_RED = 0,
		PLAYER_BLUE,
		PLAYER_YELLOW,
		PLAYER_GRAY,
		PLAYER_RONDOM,
		PLAYER_NON,
	};

	enum PC_TYPE
	{
		PC_PLAYER = 0,
		PC_CPU,
		PC_NON,
	};

	PLAYER_TYPE	pType;
	PC_TYPE		pcType;
};

namespace CharacterInfoFunc
{
	void SetCharacterInfo ( CharacterInfo* _info );

	CharacterInfo* GetCharacterInfo ();
}

#endif
