#include "Scene/Factory/TitleFactory.h"
#include "Scene/TitleScene.h"

Scene* TitleFactory::Create(){
	return new TitleScene;
}
