#ifndef _HITPOINT_H_
#define _HITPOINT_H_


class Player;

class HitPoint
{
private:
	float hp = 0;
	float maxHP;
	Player* player;

public:
	HitPoint (){}

	~HitPoint (){}

	void Init ( Player* _player );

	void IsDamage ( float _hit );

	bool IsDead ();

	void SetHP ( float _hp );

	float GetHP();

};

inline void HitPoint::SetHP ( float _hp )
{
	maxHP = hp = _hp;
}

inline float HitPoint::GetHP ()
{
	return ( hp / maxHP );
}


#endif