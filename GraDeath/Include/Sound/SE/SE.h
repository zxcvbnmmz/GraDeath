#ifndef _SE_H__
#define _SE_H__

#include <memory>

struct IXAudio2VoiceCallback;

namespace Sound{
	class SE;
}

typedef std::shared_ptr<Sound::SE> _SE;
typedef _SE SE;

namespace Sound{
class SubmixVoice;

class SE{
public:
	SE(std::shared_ptr<class SourceVoice> _sourceVoice);
	SE(std::shared_ptr<class SourceVoice> _sourceVoice, SubmixVoice* submix);
	~SE();

	bool Play(bool cueing = false);
	void Stop();
	void Pause();
	void Release();
	void SetVoume(float volume);
	void SetPitch(float pitch);
	float GetPlayingTime();
	void SetLoop(unsigned int loopBegin, unsigned int loopLength, unsigned int loopCount);
	void ExitLoop();

private:
	class SEPimpl;
	SEPimpl* pimpl;
};

extern ::SE CreateSE(char* fileName, IXAudio2VoiceCallback* callback = nullptr);
extern void SetSEVolumes(float volume);
}


#endif	// end of SE