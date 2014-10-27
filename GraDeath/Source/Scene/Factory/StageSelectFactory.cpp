#include "Scene/Factory/StageSelectFactory.h"
#include "Scene/StageSelectScene.h"

Scene* StageSelectFactory::Create(){
	return new StageSelectScene;
}