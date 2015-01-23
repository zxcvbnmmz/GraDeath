#include "Scene/Factory/CaptureFactory.h"
#include "Scene/CaptureScene/CaptureScene.h"

Scene* CaptureFactory::Create(){
	return new CaptureScene;
} 
