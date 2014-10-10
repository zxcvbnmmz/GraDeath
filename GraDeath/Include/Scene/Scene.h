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

	template<class T>
	void AddDelegateList(Scene* scene, int(Scene::*func)()){
		list.Add<T>(scene, func);
	}

	virtual SCENE_STATUS Execute() = 0;
	virtual void Draw() = 0;

	virtual void OnStack(){}

protected:
	std::vector<class SceneDelegateBase*> executes;
	std::vector<class SceneDelegateBase*> draws;
	DelegateList list;
};

#endif	// end of Scene