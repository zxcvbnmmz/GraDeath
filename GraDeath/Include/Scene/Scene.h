#ifndef _SCENE_H__
#define _SCENE_H__

#include <vector>
#include "Utility/DelegateList.h"

enum SCENE_STATUS{
	STILL_PROCESSING,
	END_PROCESS,
};

class Scene{
public:
	Scene();
	virtual ~Scene();

	virtual SCENE_STATUS Execute() = 0;
	virtual void Draw() = 0;

	virtual void OnStack(){}

protected:
	DelegateList executes;
	DelegateList draws;

	template<class T>
	void AddFunction(T* inst, int (T::*Func)(void)){
		executes.Add(Delegate<T>::Create(inst, Func));
	}

	template<class T>
	void AddFunction(T* inst, void (T::*Func)(void)){
		draws.Add(Delegate<T>::Create(inst, Func));
	}
};


#endif	// end of Scene
