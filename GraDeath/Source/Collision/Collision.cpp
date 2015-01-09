#include "Collision/Collision.h"
#include "World/World.h"
#include <Box2D\Box2D.h>

bool Collision::Collide(){
	b2Body* bodyA = NULL;
	b2Body* bodyB = NULL;

	const b2Transform& xfA = bodyA->GetTransform();
	const b2Transform& xfB = bodyB->GetTransform();
	b2Fixture* fixtureA = bodyA->GetFixtureList();
	while (fixtureA != NULL){
		const b2Shape* shapeA = fixtureA->GetShape();
		b2Fixture* fixtureB = bodyB->GetFixtureList();

		while (fixtureB != NULL){
			const b2Shape* shapeB = fixtureB->GetShape();
			bool touching = b2TestOverlap(shapeA,0, shapeB,0,xfA,xfB);
			if (touching){
				return true;
			}
			fixtureB = fixtureB->GetNext();
		}
		fixtureA = fixtureA->GetNext();
	}
	return false;
}

