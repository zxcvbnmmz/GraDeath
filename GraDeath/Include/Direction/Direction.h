#ifndef _DIRECTION_H__
#define _DIRECTION_H__

class Direction{
public:
	Direction();
	virtual ~Direction();

	static void Advance();
	static void Draw(){}

private:
	float frame;
	class Sprite* sprite;
};

#endif	// end of Direction