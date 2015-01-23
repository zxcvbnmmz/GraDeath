#include "Scene/Factory/CreditFactory.h"
#include "Scene/CreditScene.h"

Scene* CreditFactory::Create(){
	return new CreditScene;
}
