#include "Object/Factory/PlayerFactory.h"
#include "Object/Player.h"

Player* PlayerFactory::Create(){
	return new Player;
}