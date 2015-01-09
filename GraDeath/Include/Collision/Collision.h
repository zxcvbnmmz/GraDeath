#ifndef _COLLIDE_H__
#define _COLLIDE_H__

class b2Body;

namespace Collision{
	bool Collide(b2Body* bodyA, b2Body* bodyB);
}

#endif	// end of Collide

