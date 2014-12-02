// ************************************************************
// filename	CharacterController.h
// brief	Playerの管理
// name		川口　裕
// note
// 2014.10.27
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef _CHARACTER_CONTROLLER_H_
#define _CHARACTER_CONTROLLER_H_

#include <vector>
#include "Manager/AnimationManager.h"

class Player;

class CharacterController
{
public:
	CharacterController();

	virtual ~CharacterController(){}

	virtual void Init(int _padID) = 0;

	virtual void Update(class Player* _player);

	virtual void Draw(class Player* _player) = 0;

	virtual void Release() = 0;

protected:
	int padID;
	bool enable;
	AnimationManager animManager;
	CURRENT_ANIMATION_STATE currentAnimState;
	PLAYER_ACTION currentAction;

	void ChangeAction(PLAYER_ACTION newAction, bool loop);

	void(CharacterController::*Actions[ACTION_MAX])(Player*);

	virtual void Idle(Player*){}
	virtual void Run(Player*){}
	virtual void Walk(Player*){}
	virtual void Attack(Player*){}
	virtual void Damage(Player*){}
	virtual void Jump(Player*){}
};

#endif