#include "Utility/FrameTimer.h"

void FrameTimer::Set(long _time){
	time = _time;
}

int FrameTimer::Step(){
	--time;
	if (time == 0){
		return TIME_OUT;
	}
	return 0;
}