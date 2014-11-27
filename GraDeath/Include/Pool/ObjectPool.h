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
	void Erase(Ref* object);
	bool IsContains(Ref* object)const;
	unsigned int GetContainCount();

private:
	std::vector<Ref*> managedObject;
};

class ObjectPoolManager{
public:
	ObjectPool* GetCurrentPool();
	static ObjectPoolManager* GetInstance();
	static void Destroy();
	bool IsObjectInPool(Ref* object);

	friend class ObjectPool;
private:
	ObjectPoolManager();
	ObjectPoolManager(const ObjectPoolManager&);
	ObjectPoolManager& operator=(const ObjectPoolManager&);
	~ObjectPoolManager();

	void Push(ObjectPool* _pool);
	void Pop();

	static ObjectPoolManager* manager;
	std::vector<ObjectPool*> pools;
};

#endif	// end of ObjectPool