#include "World/World.h"
#include <Box2D\Box2D.h>

static const int32 velocityIterations = 6;
static const int32 positionIterations = 2;

namespace{
	b2World world(b2Vec2(0.0f, 9.8f));
}

b2Body* World::CreateBody(const b2BodyDef* def){
	return world.CreateBody(def);
}

b2Joint* World::CreateJoint(const b2JointDef* def){
	return world.CreateJoint(def);
}

void World::DestoryBody(b2Body* _body){
	world.DestroyBody(_body);
}

void World::DestoryJoint(b2Joint* _joint){
	world.DestroyJoint(_joint);
}

int World::GetBodyCount(){
	return world.GetBodyCount();
}

b2Body* World::GetBodyList(){
	return world.GetBodyList();
}

int World::GetContactCount(){
	return world.GetContactCount();
}

b2Contact* World::GetContactList(){
	return world.GetContactList();
}

void World::Step(float timeStep){
	world.Step(timeStep,velocityIterations,positionIterations);
}

void World::DrawDebugData(b2Draw* drawer){
	world.SetDebugDraw(drawer);
	world.DrawDebugData();
}

