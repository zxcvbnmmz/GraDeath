#include "CharacterController/CharacterController.h"

CharacterController::CharacterController() :currentAction(ACTION_IDLE), enable(false){
	Actions[ACTION_RUN] = &CharacterController::Run;
	Actions[ACTION_WALK] = &CharacterController::Walk;
	Actions[ACTION_ATTACK] = &CharacterController::Attack;
	Actions[ACTION_DAMAGE] = &CharacterController::Damage;
	Actions[ACTION_JUMP] = &CharacterController::Jump;
	Actions[ACTION_IDLE] = &CharacterController::Idle;
}

void CharacterController::Update(Player* _player){
	if (enable){
		currentAnimState = animManager.Update();
		(this->*Actions[currentAction])(_player);
	}
}

void CharacterController::ChangeAction(PLAYER_ACTION newAction, bool loop){
	currentAction = newAction;
	animManager.ChangeAction(newAction, loop);
}