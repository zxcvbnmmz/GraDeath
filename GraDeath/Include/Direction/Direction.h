#ifndef _DIRECTION_H__
#define _DIRECTION_H__

class Direction{
public:
	Direction();
	virtual ~Direction();

	virtual void Advance()=0;
	virtual void Draw()=0;

	class Sprite* sprite;
};

#endif	// end of Direction