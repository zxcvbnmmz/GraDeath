#include "Object/Player.h"
#include"Object/CollisionShape.h"
#include "Loader/PlayerLoader.h"


Player::Player(){
	parameter = shared_ptr< ObjectParameter > ( new ObjectParameter );
}

Player::~Player(){}

bool Player::Init(const char* fileName){
	*parameter = PlayerLoader::LoadFile ( fileName );
	return true;
}

void Player::Release(){

}

void Player::AddForce(b2Vec2& force){
	body->ApplyForce(force, body->GetWorldCenter(),true);
}

