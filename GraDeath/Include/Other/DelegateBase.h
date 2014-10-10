#ifndef _DELEGATE_BASE_H__
#define _DELEGATE_BASE_H_

class DelegateBase{
public:
	virtual ~DelegateBase(){}
	virtual void* operator()() = 0;
};

#endif	// end of DelegateBase