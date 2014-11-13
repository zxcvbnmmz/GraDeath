#include "Object/Player.h"
#include "Loader/PlayerLoader.h"

Player::Player(){
	parameter = shared_ptr< ObjectParameter > ( new ObjectParameter );
}

Player::~Player(){}

bool Player::Init(const char* fileName){

	*parameter = PlayerLoader::LoadFile ( fileName );
	return true;
}