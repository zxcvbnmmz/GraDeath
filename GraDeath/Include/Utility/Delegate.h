#ifndef _CHARACTER_DELEGATE_H__
#define _CHARACTER_DELEGATE_H__

#include "DelegateBase.h"
#include <memory>

template <class T>
class Delegate : public DelegateBase{
public:
	void* operator()(){
		return (void*)(obj->*func)();
	}

	typedef int (T::*Func)();

	static std::shared_ptr<DelegateBase> Create(T* _obj, Func _func){
		std::shared_ptr<Delegate> delegate(new Delegate);
		delegate->obj = _obj;
		delegate->func = _func;
		return delegate;
	}

private:
	Func func;
	T* obj;
};

#endif	// end of CharacterDelegate