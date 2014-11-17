#ifndef _EFFECT_H__
#define _EFFECT_H__


class Effect{
public:
	Effect();
	virtual ~Effect();

	void Update();
	virtual void Draw() = 0;
};

#endif	// end of Effect