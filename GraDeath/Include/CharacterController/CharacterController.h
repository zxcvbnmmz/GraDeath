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

class CharacterController
{
public:
	CharacterController (){}

	virtual ~CharacterController (){}

	virtual void Init (int _padID) = 0;

	virtual void Update (class Player* _player) = 0;

	virtual void Draw (class Player* _player) = 0;

	virtual void Release () = 0;

protected:
	int padID;
};

#endif