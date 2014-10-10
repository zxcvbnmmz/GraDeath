#ifndef _SCENE_MANAGER_H__
#define _SCENE_MANAGER_H__

class Scene;

namespace SceneManager{
	bool Initialize();
	int Execute();
	void Release();

	void Stack(Scene* _scene);
	void Reserve(Scene* _scene);
	void Draw();
};


#endif	// end of SceneManager