#ifndef _TITLE_FACTORY_H__
#define _TITLE_FACTORY_H__

#include "Scene/SceneFactory.h"

class TitleFactory : public SceneFactoryBase{
	Scene* Create();
};


#endif	// end of TitleFactory