#include "Object/Player.h"
#include"Object/CollisionShape.h"

Player::Player(){
	
}

Player::~Player(){}

bool Player::Init(const char* fileName){
	return true;
}

void Player::Release(){

}

void Player::AddForce(b2Vec2& force){
	body->ApplyForce(force, body->GetWorldCenter(),true);
}

