#ifndef _CAPTURE_FACTORY_H__
#define _CAPTURE_FACTORY_H__

#include "Scene/SceneFactory.h"

class CaptureFactory : public SceneFactoryBase{
	Scene* Create();
};


#endif	// end of CaptureFactory