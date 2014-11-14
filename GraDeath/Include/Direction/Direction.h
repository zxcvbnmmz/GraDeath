#ifndef _DIRECTION_H__
#define _DIRECTION_H__

class Direction{
public:
	Direction();
	virtual ~Direction();

	void Advance();
	virtual void Draw()=0;

private:
	float frame;
	class Sprite* sprite;
};

#endif	// end of Direction