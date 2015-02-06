#ifndef _WORLD_H__
#define _WORLD_H__

class b2Body;
class b2Joint;
class b2Contact;
struct b2BodyDef;
struct b2JointDef;
class b2Draw;

namespace World{
	b2Body* CreateBody(const b2BodyDef* def);
	b2Joint* CreateJoint(const b2JointDef* def);
	void DestoryBody(b2Body* _body);
	void DestoryJoint(b2Joint* _joint);
	int GetBodyCount();
	b2Body* GetBodyList();
	int GetContactCount();
	b2Contact* GetContactList();
    void SetGravity(float x, float y);
	void Step(float timeStep = 1.0f / 60.0f);
	void SetGravity(float x, float y);
	void DrawDebugData(b2Draw* drawer = nullptr);
}

#endif	// end of World