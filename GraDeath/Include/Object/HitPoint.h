#ifndef _HITPOINT_H_
#define _HITPOINT_H_


class HitPoint
{
private:
	float hp = 0;

public:
	HitPoint (){}

	~HitPoint (){}

	void Init ();

	bool IsDead ();

	void SetHP ( float _hp );

	float GetHP();

};

inline bool HitPoint::IsDead ()
{
	return ( hp <= .0f );
}

inline void HitPoint::SetHP ( float _hp )
{
	hp = _hp;
}

inline float HitPoint::GetHP ()
{
	return hp;
}

#endif