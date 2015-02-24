#ifndef _HITPOINT_MANAGER_H_
#define _HITPOINT_MANAGER_H_

class Player;

namespace HitPointManager
{
	// ������
	void Init ( int _num, Player* _player, float _hp );

	// �_���[�W

	void HitDamage(int _num, float _hit);
	void HitDamage(Player* _player, float _hit);

	void HitDamage ( int _num, float _hit );


	// HP�̎擾
	float GetHitPoint ( int _num );

	// ����
	int AlivePlayer ();

	bool IsDead ( int _num );

	int GetPlayerRanking(int _num, int& rank);

	int PlayerRanking ( int _num );


	// ��l�����ɂȂ���
	bool IsOnlyOne ();

	void Release();
}

#endif