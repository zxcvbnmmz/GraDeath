#include "CharacterController/CharacterController.h"

CharacterController::CharacterController() :currentAction(IDLE), enable(false){
	Actions[RUN] = &CharacterController::Run;
	Actions[WALK] = &CharacterController::Walk;
	Actions[ATTACK] = &CharacterController::Attack;
	Actions[DAMAGE] = &CharacterController::Damage;
	Actions[JUMP] = &CharacterController::Jump;
	Actions[IDLE] = &CharacterController::Idle;

	animManager.Create(0);
	animManager.Enable(true);
}

void CharacterController::Update(Player* _player){
	if (enable){
		animManager.Update();
		(this->*Actions[currentAction])(_player);
	}
}