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

	virtual void Init(int _padID,Player* _player) = 0;

	virtual void Update();

	virtual void Draw() = 0;

	virtual void Release() = 0;

<<<<<<< HEAD
=======
    virtual void Move(int _movex, int _movey) = 0;
    virtual void SetPos(int _posx, int _posy) = 0;
>>>>>>> Develop
protected:
	int padID;
	bool enable;
	AnimationManager animManager;
	CURRENT_ANIMATION_STATE currentAnimState;
	PLAYER_ACTION currentAction;
	Player* player;

	void ChangeAction(PLAYER_ACTION newAction, bool loop);

	void(CharacterController::*Actions[ACTION_MAX])();

	virtual void Idle(){}
	virtual void Run(){}
	virtual void Walk(){}
	virtual void Attack(){}
	virtual void Damage(){}
	virtual void Jump_Rise(){}
	virtual void Jump_Land(){}
	virtual void Skill(){}
};

#endif