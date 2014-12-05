#ifndef _SOURCE_VOICE_H__
#define _SOURCE_VOICE_H__

#include <D3DX10.h>
#include <memory>

using namespace std;

struct IXAudio2SourceVoice;
struct IXAudio2VoiceCallback;

namespace Sound{
class SubmixVoice;
struct WaveData;

class SourceVoice{
public:
	SourceVoice(shared_ptr<WaveData> _waveData, SubmixVoice* submix = nullptr, IXAudio2VoiceCallback* callback = nullptr);
	~SourceVoice();

	void SubmitBuffer(unsigned int loopBegin = 0, unsigned int loopLength = 0, unsigned int loopCount = 0);
	float GetPlayingTime();

	IXAudio2SourceVoice* const operator->(){return voice;}

private:
	IXAudio2SourceVoice* voice;
	std::shared_ptr<struct WaveData> waveData;
};
}
#endif	// end of SourceVoice