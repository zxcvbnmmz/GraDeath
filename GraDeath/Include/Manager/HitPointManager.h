#ifndef _HITPOINT_MANAGER_H_
#define _HITPOINT_MANAGER_H_

class Player;

namespace HitPointManager
{
	// ������
	void Init ( int _num, Player* _player, float _hp );

	// �_���[�W
<<<<<<< HEAD
	void HitDamage(int _num, float _hit);
	void HitDamage(Player* _player, float _hit);
=======
	void HitDamage ( int _num, float _hit );
>>>>>>> Develop

	// HP�̎擾
	float GetHitPoint ( int _num );

	// ����
	int AlivePlayer ();

<<<<<<< HEAD
	int GetPlayerRanking ( int _num );
=======
	int PlayerRanking ( int _num );
>>>>>>> Develop

	// ��l�����ɂȂ���
	bool IsOnlyOne ();

<<<<<<< HEAD

	void Release();
=======
>>>>>>> Develop
}

#endif