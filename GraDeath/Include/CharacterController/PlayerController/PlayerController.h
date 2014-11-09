// ************************************************************
// filename	PlayerController.h
// brief	Playerの管理
// name		川口　裕
// note
// 2014.10.27
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_

#include <vector>
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
private:
	std::vector< Character* > player;

public:
	PlayerController (){}

	~PlayerController (){}

	void Init ();

	void Update ();

	void Draw ();

	void Release ();

	void SetCharacter ( Character*, int );

	static PlayerController* Create ();

};

#endif