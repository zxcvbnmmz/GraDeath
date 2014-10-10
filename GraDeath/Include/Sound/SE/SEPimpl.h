#ifndef _SE_PIMPL_H__
#define _SE_PIMPL_H__

#include "SE.h"

namespace Sound{
class SubmixVoice;

class SE::SEPimpl{
public:
	SEPimpl(std::shared_ptr<class SourceVoice> _sourceVoice, SubmixVoice* submix = nullptr);
	~SEPimpl();

	bool Play(bool cueing = false);
	void Stop();
	void Pause();
	void SetVolume(float volume);
	void SetPitch(float pitch);
	float GetPlayingTime();
	void ExitLoop();
	void SetPlayingParametor();

private:
	std::shared_ptr<class SourceVoice> sourceVoice;
};

}

#endif	// end of SEPimpl