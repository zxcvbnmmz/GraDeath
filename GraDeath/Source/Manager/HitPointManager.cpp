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

	// ‰Šú‰»
	void Init ( int _num, Player* _player, float _hp )
	{
		hitPoint[ _num ].Init ( _player );
		hitPoint[ _num ].SetHP ( _hp );
		hitPoint[ _num ].SetRank(1);

		rank = 4;
	}

	void HitDamage ( int _num, float _hit )
	{
		hitPoint[ _num ].IsDamage ( _hit );
		if ( hitPoint[ _num ].IsDead () )
		{
			hitPoint[ _num ].SetRank ( rank );

			rank--;
		}
	}


	void HitDamage(Player* _player, float _hit)
	{
		for (int i = 0; i < 4; ++i){
			if (hitPoint[i].IsCompared(_player)){
				hitPoint[i].IsDamage(_hit);
				if (hitPoint[i].IsDead())
				{
					hitPoint[i].SetRank(rank);
					rank--;
				}
				break;
			}
		}
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

	// ˆêl‚¾‚¯‚É‚È‚Á‚½
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


	int GetPlayerRanking(int num, int& rank){
		if (hitPoint[num].IsEnabled()){
			rank = hitPoint[num].GetRank();
			return hitPoint[num].GetPlayerType();
		}
		rank = -1;
		return CharacterInfo::PLAYER_NON;
	}

	void Release(){
		for (int i = 0; i < 4; ++i){
			hitPoint[i].Release();
		}
	}


}