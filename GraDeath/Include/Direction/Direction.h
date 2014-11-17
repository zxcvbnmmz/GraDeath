#ifndef _DIRECTION_H__
#define _DIRECTION_H__

class Direction{
public:
	Direction(){}
	virtual ~Direction(){}

	void Advance(float elapsed = 1){
		frame += elapsed;
	}
	virtual void Draw(){}

protected:
	float frame = 0;
	class Sprite* sprite;
};

#endif	// end of Direction