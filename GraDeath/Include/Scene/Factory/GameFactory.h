#ifndef _GAME_FACTORY_H__
#define _GAME_FACTORY_H__

#include "Scene/SceneFactory.h"

class GameFactory : public SceneFactoryBase{
	Scene* Create();
};


#endif	// end of GameFactory