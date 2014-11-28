#include "Pool/ObjectPool.h"
#include "Pool/Ref.h"
#include <algorithm>

ObjectPoolManager* ObjectPoolManager::manager = nullptr;

ObjectPool::ObjectPool(){
	managedObject.reserve(200);

	ObjectPoolManager::GetInstance()->Push(this);
}

ObjectPool::~ObjectPool(){
	Clear();
	ObjectPoolManager::GetInstance()->Pop();
}

void ObjectPool::Add(Ref* ref){
	managedObject.push_back(ref);
}

void ObjectPool::Clear(){
	std::for_each(managedObject.begin(), managedObject.end(), [=](Ref* ref){
		delete ref;
		ref = nullptr;
	});

	// この要素の消し方はエラーが起きる
	// 理由は分からないが、deleteした瞬間にmanagedObjectの要素数が減っていることから
	// erase的な操作が行われている可能性あり
	// for (auto* ref : managedObject){
	//	if (ref != nullptr){
	//		delete ref;
	//	}
	//}
	managedObject.clear();
}

void ObjectPool::Erase(Ref* object){
	auto it = std::find(managedObject.begin(), managedObject.end(), object);
	if (it != managedObject.end()){
		delete (*it);
		managedObject.erase(it);
	}
}

bool ObjectPool::IsContains(Ref* object)const{
	auto it = std::find(managedObject.begin(), managedObject.end(), object);
	if (it != managedObject.end()){
		return true;
	}
	return false;
}

unsigned int ObjectPool::GetContainCount(){
	return managedObject.size();
}


ObjectPoolManager::ObjectPoolManager(){
	pools.reserve(20);
}

ObjectPoolManager::~ObjectPoolManager(){
	while (!pools.empty()){
		ObjectPool* _pool = pools.back();
		delete _pool;
	}
}

ObjectPoolManager* ObjectPoolManager::GetInstance(){
	if (manager == nullptr){
		manager = new ObjectPoolManager;
		new ObjectPool;
	}

	return manager;
}

void ObjectPoolManager::Destroy(){
	if (manager != nullptr){
		delete manager;
		manager = nullptr;
	}
}

ObjectPool* ObjectPoolManager::GetCurrentPool(){
	return pools.back();
}

bool ObjectPoolManager::IsObjectInPool(Ref* object){
	for (auto pool : pools){
		if (pool->IsContains(object)){
			return true;
		}
	}
	return false;
}

void ObjectPoolManager::Push(ObjectPool* _pool){
	pools.push_back(_pool);
}

void ObjectPoolManager::Pop(){
	pools.pop_back();
}



