#include "Object/HitPoint.h"
#include "Object/Player.h"


void HitPoint::Init ( Player* _player )
{
	player = _player;
}

void HitPoint::IsDamage ( float _hit )
{
	if ( ( hp -= _hit ) <= .0f )
	{
		//player->
	}
}

bool HitPoint::IsDead ()
{
	return ( hp <= .0f );
}