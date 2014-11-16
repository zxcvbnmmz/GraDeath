// ************************************************************
// filename	PlayerController.h
// brief	PlayerΜΗ
// name		μϋ@T
// note
// 2014.10.27
// ************************************************************

// ½dCN[hh~ ***************************************
#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_

#include "CharacterController/CharacterController.h"

class Character;

enum CHAR_NUM
{
	CHAR_RED = 0,
	CHAR_BULE,
	CHAR_GREEN,
	CHAR_YELLOW,
	CHAR_RANDOM,
	CHAR_NON,
};

class PlayerController : public CharacterController
{
public:
	PlayerController (){}

	~PlayerController (){}

	void Init (int padID);

	void Update(class Player* _player);
	void Draw(class Player* _player);


	void Release ();

private:
	virtual void Idle(Player*);
	virtual void Run(Player*);
	virtual void Walk(Player*);
	virtual void Attack(Player*);
	virtual void Damage(Player*);
	virtual void Jump(Player*);

	int count = 0;
};

#endif