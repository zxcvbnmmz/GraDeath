#ifndef _CHARACTER_DELEGATE_H__
#define _CHARACTER_DELEGATE_H__

#include "DelegateBase.h"

template <class T>
class Delegate : public DelegateBase{
public:
	void* operator()(){
		return (void*)(obj->*func)();
	}

	typedef int (T::*Func)();

	static DelegateBase* Create(T* _obj, Func _func){
		Delegate* delegate = new Delegate;
		delegate->obj = _obj;
		delegate->func = _func;
		return delegate;
	}

private:
	Func func;
	T* obj;
};

#endif	// end of CharacterDelegate