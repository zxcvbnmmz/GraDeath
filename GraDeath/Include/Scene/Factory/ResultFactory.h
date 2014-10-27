#ifndef _RESULT_FACTORY_H__
#define _RESULT_FACTORY_H__

#include "Scene/SceneFactory.h"

class ResultFactory : public SceneFactoryBase{
	Scene* Create();
};


#endif	// end of ResultFactory