#include "Other/DelegateList.h"
#include "Other/DelegateBase.h"

DelegateList::~DelegateList(){
	std::for_each(delegates.begin(), delegates.end(), [=](DelegateBase* _base){
		if (_base != nullptr){
			delete _base;
			_base = nullptr;
		}
	});
	delegates.clear();
}