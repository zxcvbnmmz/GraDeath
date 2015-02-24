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

	void Init (int padID, Player* _player, float scale);
	void Draw();
    void MovePos(int _movex, int _movey);
	void SetPos(int _posx, int _posy, float angle = 0);
	void SetDamage ();

	void Release ();

private:
	virtual void Idle();
	virtual void Run();
	virtual void Walk();
	virtual void Damage();
	virtual void Jump_Rise();
	virtual void Jump_Fall();
	virtual void Jump_Land();
	virtual void Skill();

	void Move();

	int count = 0;
	float ground;

	unsigned int dirFlg = 0;


};

#endif