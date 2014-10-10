#ifndef _BGM_H__
#define _BGM_H__

#include <memory>

namespace Sound{
	class BGM;
}

typedef std::shared_ptr<Sound::BGM> _BGM;
typedef _BGM BGM;

namespace Sound{
class SubmixVoice;

class BGM{
public:
	BGM(std::shared_ptr<class SourceVoice> _sourceVoice, SubmixVoice* submix = nullptr);
	~BGM();
	
	bool Play();
	void Stop();
	void SetVoume(float volume);
	void SetPitch(float pitch);
	float GetPlayingTime();
	void ExitLoop();
	void SetPlayingParametor();

private:
	class BGMPimpl;
	BGMPimpl* pimpl;
};

extern ::BGM CreateBGM(char* fileName);
extern void SetBGMVolumes(float volume);
}

#endif	// end of BGM