#ifndef _HITPOINT_H_
#define _HITPOINT_H_


class HitPoint
{
private:
	float hp = 0;

public:
	HitPoint ();

	~HitPoint ();

	void Init ();

	bool IsAlive ();

	float SetHP ( float _hp );

	float GetHP();

};

#endif