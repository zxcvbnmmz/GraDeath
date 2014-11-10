#include "Object/Manager/CharacterManager.h"
#include "CharacterController/PlayerController/PlayerController.h"

namespace{
	PlayerController controller;
}

bool CharacterManager::Initialize(){
	controller.Init(0);

	return true;
}

void CharacterManager::Update(){
	controller.Update();
}

void CharacterManager::Release(){
	controller.Release();
}

void CharacterManager::Draw(){
	controller.Draw();
}