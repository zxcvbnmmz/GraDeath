#ifndef _SUBMIX_VOICE_H__
#define _SUBMIX_VOICE_H__

struct IXAudio2;
struct IXAudio2SubmixVoice;

namespace Sound{
class SourceVoice;

class SubmixVoice{
friend class SourceVoice;
public:
	SubmixVoice(IXAudio2* xaudio);
	~SubmixVoice();

	void SetVolume(float volume);

private:
	IXAudio2SubmixVoice* voice;
};
}

#endif	// end of SubmixVoice