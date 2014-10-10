#ifndef _SE_H__
#define _SE_H__

#include <memory>

namespace Sound{
	class SE;
}

typedef std::shared_ptr<Sound::SE> _SE;
typedef _SE SE;

namespace Sound{
class SubmixVoice;

class SE{
public:
	SE(std::shared_ptr<class SourceVoice> _sourceVoice, SubmixVoice* submix = nullptr);
	~SE();

	bool Play(bool cueing = false);
	void Stop();
	void Pause();
	void SetVoume(float volume);
	void SetPitch(float pitch);
	float GetPlayingTime();
	void ExitLoop();
	void SetPlayingParametor();

private:
	class SEPimpl;
	SEPimpl* pimpl;
};

extern ::SE CreateSE(char* fileName);
extern void SetSEVolumes(float volume);
}


#endif	// end of SE