#include "Scene/Factory/ResultFactory.h"
#include "Scene/ResultScene.h"

Scene* ResultFactory::Create(){
	return new ResultScene;
}