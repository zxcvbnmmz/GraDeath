#ifndef _FRAME_TIMER_H__
#define _FRAME_TIMER_H__

class FrameTimer{
public:
	void Set(long _time);

	enum TIME_STATUS{
		TIME_OUT = 0xffff
	};

	int Step();
	
private:
	long time;
};

#endif	// end of FrameTimer