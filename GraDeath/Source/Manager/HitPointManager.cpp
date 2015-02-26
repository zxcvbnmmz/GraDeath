#include "Object/Player.h"
#include "Manager/HitPointManager.h"
#include "Object/HitPoint.h"
#include "Manager/SkillManager.h"

namespace HitPointManager
{
	namespace
	{
		HitPoint hitPoint[ 4 ];
		bool checkFlg[4];
		unsigned int rank;
	}

	// ‰Šú‰»
	void Init ( int _num, Player* _player, float _hp )
	{
		hitPoint[ _num ].Init ( _player );
		hitPoint[ _num ].SetHP ( _hp );
		hitPoint[ _num ].SetRank(1);
		checkFlg[_num] = true;
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
				SkillManager::SetSPGage(i, _hit);
				if (hitPoint[i].IsDead() && checkFlg[i])
				{
					checkFlg[i] = false;
					hitPoint[i].SetRank(rank);
					rank--;
				}
				break;
			}
		}
	}

	void HitDamageEx(Player* _player, float _hit)
	{
		for (int i = 0; i < 4; ++i){
			if (hitPoint[i].IsEnabled() && !hitPoint[i].IsCompared(_player)){
				hitPoint[i].IsDamage(_hit);
				SkillManager::SetSPGage(i, _hit * 0.05f);
				if (hitPoint[i].IsDead() && checkFlg[i])
				{
					checkFlg[i] = false;
					hitPoint[i].SetRank(rank);
					rank--;
				}
				break;
			}
		}
	}

	void HitDamageEx(int _num, float _hit)
	{
		for (int i = 0; i < 4; ++i){
			if (i != _num && hitPoint[_num].IsEnabled()){
				hitPoint[i].IsDamage(_hit);
				if (hitPoint[i].IsDead())
				{
					hitPoint[i].SetRank(rank);
					rank--;
				}
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

	bool IsDead ( int _num )
	{
		return hitPoint[ _num ].IsDead ();
	}

	// ˆêl‚¾‚¯‚É‚È‚Á‚½
	bool IsOnlyOne ()
	{
		bool temp = false;
		int count = 0;
		for ( int i = 0; i < 4; i++ )
		{
			if ( hitPoint[ i ].IsDead () )
				count++;
			//if ( temp == !hitPoint[ i ].IsDead () )
			//	return false;

			//if ( !hitPoint[ i ].IsDead () )
			//	temp = true;
		}
		return ( count == 3 ) ? true : false;//temp;
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