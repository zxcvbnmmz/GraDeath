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
#include <D3DX10math.h>

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

	void Init (int padID, Player* _player);
	void Draw();

	void Release ();

private:
	virtual void Idle();
	virtual void Run();
	virtual void Walk();
	virtual void Attack();
	virtual void Damage();
	virtual void Jump();

	int count = 0;
	// κIΙιΎ
	D3DXVECTOR2 pos;
	float ground;
};

#endif