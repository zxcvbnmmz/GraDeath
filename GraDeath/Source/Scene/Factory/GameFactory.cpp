#include "Scene/Factory/GameFactory.h"
#include "Scene/GameScene.h"

Scene* GameFactory::Create(){
	return new GameScene;
}