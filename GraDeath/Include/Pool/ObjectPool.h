#ifndef _OBJECT_POOL_H__
#define _OBJECT_POOL_H__

#include <vector>

class Ref;

class ObjectPool{
public:
	ObjectPool();
	~ObjectPool();

	void Add(Ref* object);
	void Clear();
	bool IsContains(Ref* object)const;

private:
	std::vector<Ref*> managedObject;
};

class ObjectPoolManager{
public:
	void Add();
	ObjectPool* GetCurrentPool();
	bool IsObjectInPool();


	friend class ObjectPool;
private:
	ObjectPoolManager();
	ObjectPoolManager(const ObjectPoolManager&);
	ObjectPoolManager& operator=(const ObjectPoolManager&);
	~ObjectPoolManager();

	static ObjectPoolManager* manager;
	std::vector<ObjectPool*> pool;
};

#endif	// end of ObjectPool