#ifndef _SELECT_ICON_H_
#define _SELECT_ICON_H_

#include <memory>
#include "D2D/Sprite/Sprite.h"



class SelectIcon
{
private:
	struct IconState;
	IconState* iconState;

	Sprite iconSprite;
	Sprite charSprite[ 4 ];

public:
	SelectIcon ();

	~SelectIcon ();

	void SetUp ();

	void Draw ();

	void ChangeIcon ( int, int );

};


#endif