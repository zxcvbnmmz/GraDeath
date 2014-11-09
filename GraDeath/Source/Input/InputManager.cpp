#include "Input/InputManager.h"
#include "Input/Gamepad.h"
#include "Input/Keyboard.h"

bool InputManager::Initialize(){
	GamePad::init();

	return true;
}

void InputManager::Update(){
	GamePad::update();
	Keyboard::Update();
}