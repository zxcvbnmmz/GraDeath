#include "Manager/HitPointManager.h"
#include "Object/HitPoint.h"
#include "Object/Player.h"

namespace HitPointManager
{
	namespace
	{
		HitPoint hitPoint[ 4 ];
		unsigned int rank;
	}

	// 初期化
	void Init ( int _num, Player* _player, float _hp )
	{
		hitPoint[ _num ].Init ( _player );
		hitPoint[ _num ].SetHP ( _hp );
		rank = 4;
	}

	// ダメージ
	void HitDamage ( int _num, float _hit )
	{
		hitPoint[ _num ].IsDamage ( _hit );
		if ( hitPoint[ _num ].IsDead () )
		{
			hitPoint[ _num ].SetRank ( rank );
			rank--;
		}
	}

	// HPの取得
	float GetHitPoint ( int _num )
	{
		return hitPoint[ _num ].GetHP();
	}

	// 勝者
	int AlivePlayer ()
	{
		float tempHP = .0f;
		int tempNum = 5;

		for ( int i = 0; i < 4; i++ )
		{
			if ( hitPoint[ i ].IsDead () )
				continue;

			if ( tempHP < hitPoint[ i ].GetHP () )
			{
				tempHP = hitPoint[ i ].GetHP ();
				tempNum = i;
			}			
		}
		return tempNum;
	}

	// 一人だけになった
	bool IsOnlyOne ()
	{
		bool temp = false;
		for ( int i = 0; i < 4; i++ )
		{
			if ( temp == !hitPoint[ i ].IsDead () )
				return false;

			if ( !hitPoint[ i ].IsDead () )
				temp = true;
		}
		return temp;
	}

}