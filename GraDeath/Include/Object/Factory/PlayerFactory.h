#ifndef _PLAYER_FACTORY_H__
#define _PLAYER_FACTORY_H__

enum class PLAYER_ID{

};

struct PlayerFactory{
	PLAYER_ID id;
	class Player* Create();
};

#endif	// end of PlayerFactory