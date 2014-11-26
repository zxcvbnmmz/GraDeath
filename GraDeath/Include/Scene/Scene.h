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
	std::vector<class DelegateBase*> executes;
	std::vector<class DelegateBase*> draws;
	DelegateList list;
};

#define ADD_DELEGATE(CLASS,INST,FUNC)				\
	list.Add(Delegate<CLASS>::Create(INST,FUNC))	\

#endif	// end of Scene