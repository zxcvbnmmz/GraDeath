#ifndef _HITPOINT_MANAGER_H_
#define _HITPOINT_MANAGER_H_

class Player;

namespace HitPointManager
{
	// 初期化
	void Init ( int _num, Player* _player, float _hp );

	// ダメージ
<<<<<<< HEAD
	void HitDamage(int _num, float _hit);
	void HitDamage(Player* _player, float _hit);
=======
	void HitDamage ( int _num, float _hit );
>>>>>>> Develop

	// HPの取得
	float GetHitPoint ( int _num );

	// 勝者
	int AlivePlayer ();

<<<<<<< HEAD
	int GetPlayerRanking ( int _num );
=======
	int PlayerRanking ( int _num );
>>>>>>> Develop

	// 一人だけになった
	bool IsOnlyOne ();

<<<<<<< HEAD

	void Release();
=======
>>>>>>> Develop
}

#endif