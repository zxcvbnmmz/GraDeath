// ************************************************************
// filename	PlayerController.h
// brief	Player�̊Ǘ�
// name		����@�T
// note
// 2014.10.27
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_

#include <vector>
#include "CharacterController/CharacterController.h"


class Character;


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