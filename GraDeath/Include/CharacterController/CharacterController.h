// ************************************************************
// filename	CharacterController.h
// brief	Player�̊Ǘ�
// name		����@�T
// note
// 2014.10.27
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef _CHARACTER_CONTROLLER_H_
#define _CHARACTER_CONTROLLER_H_

#include <vector>

class Player;

class CharacterController
{
public:
	CharacterController();

	virtual ~CharacterController(){}

	virtual void Init(int _padID) = 0;

	virtual void Update(class Player* _player) = 0;

	virtual void Draw(class Player* _player) = 0;

	virtual void Release() = 0;

protected:
	int padID;
	bool enable;

	// �ȉ�����̎����ɂ������邩��

	enum PLAYER_ACTION : unsigned int {
		IDLE,
		RUN,
		WALK,
		ATTACK,
		DAMAGE,
		JUMP,
		NOTHING,
		ACTION_MAX
	}currentAction;
	void(CharacterController::*Actions[ACTION_MAX])(Player*);

	virtual void Idle(Player*){}
	virtual void Run(Player*){}
	virtual void Walk(Player*){}
	virtual void Attack(Player*){}
	virtual void Damage(Player*){}
	virtual void Jump(Player*){}
};

#endif