#ifndef _SCENE_FACTORY_H__
#define _SCENE_FACTORY_H__

class SceneFactoryBase;

namespace SceneFactory{
	void Stack(SceneFactoryBase* _factory);
	void Reserve(SceneFactoryBase* _factory);
};

class SceneFactoryBase{
public:
	virtual class Scene* Create() = 0;

protected:
	SceneFactoryBase(){}

private:
	SceneFactoryBase(const SceneFactoryBase&);
	SceneFactoryBase& operator=(const SceneFactoryBase&);
	void* operator new(size_t);
};


#endif	// end of SceneFactory