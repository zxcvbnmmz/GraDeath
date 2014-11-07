#ifndef _CHARACTER_H__
#define _CHARACTER_H__

#include "Object.h"

typedef void* CharacterData;

class Character : public Object{
	friend class CharacterController;

public:
	Character(CharacterData data);
	virtual ~Character(){}

private:
	void* ID;
	class CwnSkinMesh* mesh;
	class CwnSkinMesh* collisionMesh;
};

#endif	// end of Character
