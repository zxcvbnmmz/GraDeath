#ifndef _STAGE_SELECT_FACTORY_H__
#define _STAGE_SELECT_FACTORY_H__

#include "Scene/SceneFactory.h"

class StageSelectFactory : public SceneFactoryBase{
	Scene* Create();
};

#endif	// end of CharacterSelectFactory