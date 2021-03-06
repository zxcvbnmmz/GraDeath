// ************************************************************
// filename	CharacterController.h
// brief	PlayerΜΗ
// name		μϋ@T
// note
// 2014.10.27
// ************************************************************

// ½dCN[hh~ ***************************************
#ifndef _CHARACTER_CONTROLLER_H_
#define _CHARACTER_CONTROLLER_H_

#include <vector>
#include "Manager/AnimationManager.h"
#include "Manager/VoiceManager.h"

class Player;

class CharacterController
{
public:
	CharacterController();

	virtual ~CharacterController(){}

	virtual void Init(int _padID,Player* _player, float scale) = 0;

	virtual void Update();

	virtual void Draw() = 0;

	virtual void Release() = 0;

	virtual void SetDamage () = 0;

	PLAYER_ACTION GetCurrentAction();

    virtual void MovePos(int _movex,int _movey) = 0;

    virtual void SetPos(int _posx, int _posy, float angle = 0) = 0;
	void ChangeAction(PLAYER_ACTION newAction, bool loop, PLAYER_DIRECTION _dir = SAME_BEFORE);
	void Enable(bool _enable);

protected:
	int padID;
	bool enable;
	AnimationManager animManager;
	CURRENT_ANIMATION_STATE currentAnimState;
	PLAYER_ACTION currentAction;
	Player* player;
	VoiceManager voiceManager;

	void(CharacterController::*Actions[ACTION_MAX])();

	virtual void Idle(){}
	virtual void Run(){}
	virtual void Walk(){}
	virtual void Attack(){}
	virtual void Damage(){}
	virtual void Jump_Rise(){}
	virtual void Jump_Fall(){}
	virtual void Jump_Land(){}
	virtual void Skill(){}
};

#endif