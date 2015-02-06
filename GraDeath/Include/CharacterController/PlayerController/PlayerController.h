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

	void Init (int padID, Player* _player);
	void Draw();

    void SetPos(int _posx, int _posy);
	PLAYER_ACTION GetCurrentAction();


	void Release ();

private:
	virtual void Idle();
	virtual void Run();
	virtual void Walk();
	virtual void Attack();
	virtual void Damage();
	virtual void Jump_Rise();
	virtual void Jump_Land();
	virtual void Skill();

	int count = 0;
	// 一時的に宣言
	D3DXVECTOR2 pos;
	float ground;

	unsigned int dirFlg = 0;
};

#endif