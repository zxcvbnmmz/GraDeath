#ifndef _CHARACTER_SELECT_FACTORY_H__
#define _CHARACTER_SELECT_FACTORY_H__

#include "Scene/SceneFactory.h"

class CharacterSelectFactory : public SceneFactoryBase{
	Scene* Create();
};

#endif	// end of CharacterSelectFactory