#ifndef _HITPOINT_MANAGER_H_
#define _HITPOINT_MANAGER_H_

class Player;

namespace HitPointManager
{
	// ‰Šú‰»
	void Init ( int _num, Player* _player, float _hp );

	// ƒ_ƒ[ƒW
	void HitDamage ( int _num, float _hit );

	// HP‚Ìæ“¾
	float GetHitPoint ( int _num );

	// ŸÒ
	int AlivePlayer ();

}

#endif