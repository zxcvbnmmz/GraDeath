#include "Utility/DelegateList.h"
#include "Utility/DelegateBase.h"

DelegateList::~DelegateList(){
	for (auto delegateBase : delegates){
		//delegateBase.reset();
	}
}