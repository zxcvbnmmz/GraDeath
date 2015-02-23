#include "CharacterController/CharacterController.h"

CharacterController::CharacterController() :currentAction(ACTION_IDLE), enable(false){
	Actions[ACTION_WALK] = &CharacterController::Walk;
	Actions[ACTION_JUMP_RISE] = &CharacterController::Jump_Rise;
	Actions[ACTION_JUMP_FALL] = &CharacterController::Jump_Fall;
	Actions[ ACTION_JUMP_LAND ] = &CharacterController::Jump_Land;
	Actions[ ACTION_SKILL ] = &CharacterController::Skill;
	Actions[ ACTION_SKILL_2 ] = &CharacterController::Skill;
	Actions[ ACTION_SKILL_3 ] = &CharacterController::Skill;
	Actions[ACTION_IDLE] = &CharacterController::Idle;
	Actions[ ACTION_DAMAGE ] = &CharacterController::Damage;
}

void CharacterController::Update(){
	if (enable){
		currentAnimState = animManager.Update();
		(this->*Actions[currentAction])();
	}
}

void CharacterController::ChangeAction(PLAYER_ACTION newAction, bool loop, PLAYER_DIRECTION _dir){
	currentAction = newAction;
	animManager.ChangeAction(newAction, loop, _dir);
}

PLAYER_ACTION CharacterController::GetCurrentAction(){
	return currentAction;
}

