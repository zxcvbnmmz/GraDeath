#ifndef _DELEGATE_LIST_H__
#define _DELEGATE_LIST_H__

#include <vector>
#include <algorithm>

class DelegateList{
public:
	~DelegateList();

	void Add(class DelegateBase* _delegate){
		delegates.push_back(_delegate);
	}
		
	class DelegateBase* operator[](int index){
		return delegates[index];
	}

private:
	std::vector<class DelegateBase*> delegates;
};

#endif	// end of DelegateList