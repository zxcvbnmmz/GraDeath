#ifndef _BGM_PIMPL_H__
#define _BGM_PIMPL_H__

#include "BGM.h"

namespace Sound{
class SubmixVoice;

class BGM::BGMPimpl{
public:
	BGMPimpl(std::shared_ptr<class SourceVoice> _sourceVoice, SubmixVoice* submix = nullptr);
	~BGMPimpl();

	bool Play();
	void Stop();
	void SetVolume(float volume);
	void SetPitch(float pitch);
	float GetPlayingTime();
	void SetLoop ( unsigned int loopBegin, unsigned int loopEnd, unsigned int loopCount );
	void ExitLoop ();
	void SetPlayingParametor ();

private:
	std::shared_ptr<class SourceVoice> sourceVoice;
	unsigned int loopBegin = 0;
	unsigned int loopLength = 0;
	unsigned int loopCount = 0;
};


}

#endif	// end of BGMPimpl