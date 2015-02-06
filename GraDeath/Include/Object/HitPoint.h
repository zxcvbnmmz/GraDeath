#ifndef _HITPOINT_H_
#define _HITPOINT_H_


class Player;

class HitPoint
{
private:
	int rank = 0;
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

	void SetRank ( int _rank );

	int GetRank ();
	bool IsCompared(Player* _player);
	bool IsEnabled();
	void Release();
};

inline void HitPoint::SetHP ( float _hp )
{
	maxHP = hp = _hp;
}

inline float HitPoint::GetHP ()
{
	return ( hp / maxHP );
}

inline void HitPoint::SetRank ( int _rank )
{
	rank = _rank;
}

inline int HitPoint::GetRank ()
{
	return rank;
}

#endif