#include "CharacterController/CharacterController.h"

CharacterController::CharacterController() :currentAction(ACTION_IDLE), enable(false){
	Actions[ACTION_RUN] = &CharacterController::Run;
	Actions[ACTION_WALK] = &CharacterController::Walk;
	Actions[ACTION_ATTACK] = &CharacterController::Attack;
	Actions[ACTION_DAMAGE] = &CharacterController::Damage;
	Actions[ACTION_JUMP_RISE] = &CharacterController::Jump_Rise;
	Actions[ACTION_JUMP_FALL] = &CharacterController::Jump_Fall;
	Actions[ACTION_JUMP_LAND] = &CharacterController::Jump_Land;
	Actions[ACTION_SKILL] = &CharacterController::Skill;
	Actions[ACTION_IDLE] = &CharacterController::Idle;
}

void CharacterController::Update(){
	if (enable){
		currentAnimState = animManager.Update();
		(this->*Actions[currentAction])();
	}
}

void CharacterController::ChangeAction(PLAYER_ACTION newAction, bool loop){
	currentAction = newAction;
	animManager.ChangeAction(newAction, loop);
}

PLAYER_ACTION CharacterController::GetCurrentAction(){
	return currentAction;
}

void CharacterController::Reverse(bool _reverse){
	animManager.Reverse(_reverse);
}

