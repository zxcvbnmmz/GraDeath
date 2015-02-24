#ifndef _HITPOINT_MANAGER_H_
#define _HITPOINT_MANAGER_H_

class Player;

namespace HitPointManager
{
	// 初期化
	void Init ( int _num, Player* _player, float _hp );

	// ダメージ

	void HitDamage(int _num, float _hit);
	void HitDamage(Player* _player, float _hit);

	void HitDamage ( int _num, float _hit );


	// HPの取得
	float GetHitPoint ( int _num );

	// 勝者
	int AlivePlayer ();

	bool IsDead ( int _num );

	int GetPlayerRanking(int _num, int& rank);

	int PlayerRanking ( int _num );


	// 一人だけになった
	bool IsOnlyOne ();

	void Release();
}

#endif