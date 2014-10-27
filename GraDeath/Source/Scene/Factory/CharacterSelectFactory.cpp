#include "Scene/Factory/CharacterSelectFactory.h"
#include "Scene/CharacterSelectScene.h"

Scene* CharacterSelectFactory::Create(){
	return new CharacterSelectScene;
}