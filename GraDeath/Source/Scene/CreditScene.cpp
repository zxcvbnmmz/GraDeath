#include "Scene/CreditScene.h"
#include "Scene/Factory/TitleFactory.h"
#include "Input/Gamepad.h"
#include "Input\Keyboard.h"
#include "Utility/Delegate.h"

CreditScene::CreditScene(){
	currentState = NORMAL;
}

CreditScene::~CreditScene(){

}

SCENE_STATUS CreditScene::Execute(){
	int status = (int)(*executes[currentState])();

	if (Keyboard::CheckKey(KC_R) == INPUT_STATE::INPUT_PUSH){
		TitleFactory cf;
		SceneFactory::Reserve(&cf);
		return END_PROCESS;
	}

	return (SCENE_STATUS)status;
}

void CreditScene::Draw(){
	(*draws[currentState])();
}

