#include "Sound/Voice/SourceVoice.h"
#include "Sound/Voice/SubmixVoice.h"
#include "Sound/SoundCore.h"
#include "Sound/WaveData.h"
#include <XAudio2.h>

namespace Sound{
SourceVoice::SourceVoice(std::shared_ptr<struct WaveData> _waveData, SubmixVoice* submix):voice(nullptr),waveData(_waveData){
	WAVEFORMATEX* ex = waveData.get()->wfex;
	HRESULT hr;

	if(submix == nullptr){
		IXAudio2* audio = SoundCore::GetXAudio();
		HRESULT hr = SoundCore::GetXAudio()->CreateSourceVoice(&voice,ex);
	}else{
		XAUDIO2_SEND_DESCRIPTOR descriptor;
		descriptor.Flags = 0;
		descriptor.pOutputVoice = submix->voice;

		XAUDIO2_VOICE_SENDS SFXSendList;
		SFXSendList.pSends = &descriptor;
		SFXSendList.SendCount = 1;
		hr = SoundCore::GetXAudio()->CreateSourceVoice(&voice,ex,0U,2.0F,NULL,&SFXSendList);
	}

    XAUDIO2_BUFFER buffer = {0};
	buffer.pAudioData = waveData->waveBuffer;
    buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = waveData->waveSize;
	voice->SubmitSourceBuffer(&buffer);
}

SourceVoice::~SourceVoice(){
	if(voice){
		voice->DestroyVoice();
		voice = nullptr;
	}
}

void SourceVoice::SubmitBuffer(){
	voice->FlushSourceBuffers();

    XAUDIO2_BUFFER buffer = {0};
	buffer.pAudioData = waveData->waveBuffer;
    buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = waveData->waveSize;
	voice->SubmitSourceBuffer(&buffer);
}

float SourceVoice::GetPlayingTime(){
	return (float)waveData->waveSize / (float)waveData->wfex->nAvgBytesPerSec;
}

}