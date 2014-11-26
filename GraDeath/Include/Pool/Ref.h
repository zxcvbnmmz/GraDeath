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
	__declspec(deprecated("Please use Derived class's function"))CREATE(Ref);

private:
	unsigned int refCount;
};

#endif	// end of Ref