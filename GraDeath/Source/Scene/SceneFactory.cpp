#include "Scene/SceneFactory.h"
#include "Scene/SceneManager.h"

void SceneFactory::Stack(SceneFactoryBase* _factory){
	SceneManager::Stack(_factory->Create());
}

void SceneFactory::Reserve(SceneFactoryBase* _factory){
	SceneManager::Reserve(_factory->Create());
}

