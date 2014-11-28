#ifndef _EFFECT_H__
#define _EFFECT_H__

#include "Pool/Ref.h"

REF_CLASS(Effect){
public:
	Effect();
	virtual ~Effect();

	void Update();
	virtual void Draw(){
		auto effect = Effect::Create();
		ObjectPoolManager::GetInstance()->GetCurrentPool()->Erase(effect);
	}

	CREATE(Effect);
};

#endif	// end of Effect

