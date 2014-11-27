#include "Pool/Ref.h"
#include "Pool/ObjectPool.h"

Ref::Ref() :refCount(1) {}

Ref* Ref::AddReleasedList(){
	ObjectPoolManager::GetInstance()->GetCurrentPool()->Add(this);
	return this;
}

void Ref::Release(){
	--refCount;
	if (refCount == 0){
		ObjectPoolManager::GetInstance()->GetCurrentPool()->Erase(this);
	}
}

