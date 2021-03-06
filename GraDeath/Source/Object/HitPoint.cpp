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
		hp = 0.f;
		player->Destroy();
		player->IsCollidable = false;
	}
}

bool HitPoint::IsDead ()
{
	return ( hp <= .0f );
}

bool HitPoint::IsCompared(Player* _player){
	return player == _player;
}

bool HitPoint::IsEnabled(){
	return player != nullptr;
}

void HitPoint::Release(){
	player = nullptr;
	rank = 0;
	hp = 0;
	maxHP = 0;
}

int HitPoint::GetPlayerType(){
	return player->GetPlayerType();
}