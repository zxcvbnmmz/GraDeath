#ifndef _SCENE_MANAGER_H__
#define _SCENE_MANAGER_H__

class Scene;

#ifdef _DEBUG
#include "D2D/Text/TextObject.h"
#endif

namespace SceneManager{
	bool Initialize();
	int Execute();
	void Release();

	void Stack(Scene* _scene);
	void Reserve(Scene* _scene);
	void Draw();

#ifdef _DEBUG
	static D2D::TextObject t;
#endif
};


#endif	// end of SceneManager