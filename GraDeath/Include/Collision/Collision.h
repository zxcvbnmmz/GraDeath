#ifndef _COLLIDE_H__
#define _COLLIDE_H__

class Player;
class b2Body;

namespace Collision{
	bool Collide(Player* bodyA, Player* bodyB);
	bool CollideToStage(Player* body, b2Body* breakableStage);
	bool CollideOtherFloors(Player* body, b2Body* unbreakableStage);
}

#endif	// end of Collide

