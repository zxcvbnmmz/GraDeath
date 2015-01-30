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

	// ������
	void Init ( int _num, Player* _player, float _hp )
	{
		hitPoint[ _num ].Init ( _player );
		hitPoint[ _num ].SetHP ( _hp );
		rank = 4;
	}

	// �_���[�W
	void HitDamage ( int _num, float _hit )
	{
		hitPoint[ _num ].IsDamage ( _hit );
		if ( hitPoint[ _num ].IsDead () )
		{
			hitPoint[ _num ].SetRank ( rank );
			rank--;
		}
	}

	// HP�̎擾
	float GetHitPoint ( int _num )
	{
		return hitPoint[ _num ].GetHP();
	}

	// ����
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

	// ��l�����ɂȂ���
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