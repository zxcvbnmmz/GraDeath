#ifndef _DELEGATE_LIST_H__
#define _DELEGATE_LIST_H__

#include <vector>
#include <memory>

class DelegateList{
public:
	~DelegateList();

	void Add(std::shared_ptr<class DelegateBase> _delegate){
		delegates.push_back(_delegate);
	}
		
	class DelegateBase* operator[](int index){
		return delegates[index].get();
	}

private:
	std::vector<std::shared_ptr<class DelegateBase>> delegates;
};

#endif	// end of DelegateList