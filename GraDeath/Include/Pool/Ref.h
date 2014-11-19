#ifndef _REF_H__
#define _REF_H__

#include "ObjectPool.h"

class Ref{
protected:
	Ref();
	Ref* AddReleasedList();

public:
	virtual ~Ref(){}
	void Release();

private:
	unsigned int refCount;
};

#endif	// end of Ref