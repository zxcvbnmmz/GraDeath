#include "Utility/DelegateList.h"
#include "Utility/DelegateBase.h"

DelegateList::~DelegateList(){
	std::for_each(delegates.begin(), delegates.end(), [=](DelegateBase* _base){
		if (_base != nullptr){
			delete _base;
			_base = nullptr;
		}
	});
	delegates.clear();
}