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