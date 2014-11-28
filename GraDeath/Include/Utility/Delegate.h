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

	template<class R>
	static std::shared_ptr<DelegateBase> Create(T* _obj, R(T::*_func)(void)){
		std::shared_ptr<Delegate> delegate(new Delegate);
		delegate->obj = _obj;
		delegate->func = reinterpret_cast<void* (T::*)(void)>(_func);
		return delegate;
	}

private:
	void* (T::*func)(void);
	T* obj;
};

#endif	// end of CharacterDelegate