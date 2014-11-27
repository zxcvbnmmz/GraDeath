#ifndef _MACRO_H__
#define _MACRO_H__

#define DEPRECATED __declspec(deprecated)

#define CREATE(C)								\
static C* Create(){								\
	C* c = new C;								\
	if(c != nullptr){							\
		ObjectPoolManager::GetInstance()->		\
					GetCurrentPool()->Add(c);	\
		return c;								\
	}											\
	return nullptr;								\
}

#define REF_CLASS(CLASS) CLASS : public Ref



#endif	// end of Macro