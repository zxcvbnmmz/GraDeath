#include "Manager/HitPointManager.h"
#include "Object/HitPoint.h"
#include "Object/Player.h"

namespace HitPointManager
{
	namespace
	{
		HitPoint hitPoint[ 4 ];
	}

	// ‰Šú‰»
	void Init ( int _num, Player* _player, float _hp )
	{
		hitPoint[ _num ].Init ( _player );
		hitPoint[ _num ].SetHP ( _hp );
	}

	// ƒ_ƒ[ƒW
	void HitDamage ( int _num, float _hit )
	{
		hitPoint[ _num ].IsDamage ( _hit );
	}

	// HP‚Ìæ“¾
	float GetHitPoint ( int _num )
	{
		return hitPoint[ _num ].GetHP();
	}

	// ŸÒ
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
}