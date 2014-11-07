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


#define PLAYER_NUM ( 4 )

#include <vector>

class Character;

class CharacterController
{
public:
	CharacterController (){}

	virtual ~CharacterController (){}

	virtual void Init () = 0;

	virtual void Update () = 0;

	virtual void Draw () = 0;
	void Draw(Character* character);

	virtual void Release () = 0;

};

#endif