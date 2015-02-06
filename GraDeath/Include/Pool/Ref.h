#ifndef _REF_H__
#define _REF_H__

#include "ObjectPool.h"
#include "Utility/Macro.h"

class Ref{
protected:
	Ref();
	Ref* AddReleasedList();

public:
	virtual ~Ref(){}
	void Release();

	// 派生クラスでCreateマクロが実装されていない場合、Ref::Createが呼ばれる
	// この関数はdeprecatedにより使用を禁止しているので、派生クラスでのCreate関数の実装を強要している
	__declspec(deprecated("Please use the function of a derived class"))CREATE(Ref);

private:
	unsigned int refCount;
};

#endif	// end of Ref