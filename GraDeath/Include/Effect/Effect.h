#ifndef _EFFECT_H__
#define _EFFECT_H__

#include "Pool/Ref.h"

class REF_CLASS(Effect){
public:
	Effect();
	virtual ~Effect();

	void Update();
	virtual void Draw(){}

	CREATE(Effect);
};

#endif	// end of Effect

