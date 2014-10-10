#ifndef _SOURCE_VOICE_H__
#define _SOURCE_VOICE_H__

#include <D3DX10.h>
#include <memory>

struct IXAudio2SourceVoice;

namespace Sound{
class SubmixVoice;

class SourceVoice{
public:
	SourceVoice(std::shared_ptr<struct WaveData> _waveData, SubmixVoice* submix = nullptr);
	~SourceVoice();

	void SubmitBuffer();
	float GetPlayingTime();

	IXAudio2SourceVoice* const operator->(){return voice;}

private:
	IXAudio2SourceVoice* voice;
	std::shared_ptr<struct WaveData> waveData;
};
}
#endif	// end of SourceVoice