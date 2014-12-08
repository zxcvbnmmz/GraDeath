#ifndef _HITPOINT_MANAGER_H_
#define _HITPOINT_MANAGER_H_

class Player;

namespace HitPointManager
{
	// ������
	void Init ( int _num, Player* _player, float _hp );

	// �_���[�W
	void HitDamage ( int _num, float _hit );

	// HP�̎擾
	float GetHitPoint ( int _num );

	// ����
	int AlivePlayer ();

	// ��l�����ɂȂ���
	bool IsOnlyOne ();

}

#endif