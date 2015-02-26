#ifndef _COLLIDE_H__
#define _COLLIDE_H__

class Player;
class b2Body;
class Skill;
class CharacterController;

namespace Collision{
	bool Collide(Player* bodyA, Player* bodyB);
	bool CollideToStage(Player* body, b2Body* stage, CharacterController* controller);
	bool CollideFloor(Player* body, b2Body* floor, CharacterController* controller);
	bool CollideSkill(Player* body, b2Body* skill);
	bool CollideSkillToStage ( b2Body* stage, b2Body* skill, int _num );
}

#endif	// end of Collide

