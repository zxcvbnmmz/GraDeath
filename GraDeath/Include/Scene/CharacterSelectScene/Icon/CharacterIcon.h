#ifndef _CHARACTER_ICON_H_
#define _CHARACTER_ICON_H_

#include <memory>
#include "D2D/Sprite/Sprite.h"



class CharacterIcon
{
private:
	Sprite charSprite[ 5 ];

public:
	CharacterIcon ();

	~CharacterIcon ();

	void SetUp ();

	void Draw ();

};


#endif