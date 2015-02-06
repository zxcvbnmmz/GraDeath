#ifndef _COLLIDE_H__
#define _COLLIDE_H__

class Player;
class b2Body;
class Skill;
class CharacterController;

namespace Collision{
	bool Collide(Player* bodyA, Player* bodyB);
	bool CollideToStage(Player* body, b2Body* breakableStage);
	bool CollideToSkill(Player* player);
	bool CollideOtherFloors(Player* body, b2Body* unbreakableStage, CharacterController* controller);
	bool CollideSkill(Player* body, Skill* skill);
}

#endif	// end of Collide

