#include "Sound/SE/SE.h"
#include "Sound/Sound.h"
#include "Sound/BGM/BGM.h"
#include "Sound/WaveDecoder.h"
#include "Sound/Voice/MasterVoice.h"
#include "Sound/Voice/SourceVoice.h"
#include "Sound/Voice/SubmixVoice.h"
#include "Sound/SoundCore.h"
#include <memory>

namespace Sound{
	std::shared_ptr<SubmixVoice> submixSE;
	std::shared_ptr<SubmixVoice> submixBGM;
}

Sound::SourceVoice* Decode(char* fileName);

bool Sound::Initialize(){
	IXAudio2* xaudio = SoundCore::GetXAudio();
	if(xaudio){
		return false;
	}

	bool hr =  SoundCore::Initialize();
	if(!hr){
		return false;
	}
	xaudio = SoundCore::GetXAudio();
	
	submixSE.reset(new SubmixVoice(xaudio));
	submixBGM.reset(new SubmixVoice(xaudio));

	return true;
}

void Sound::Release(){
	submixBGM.reset();
	submixSE.reset();

	SoundCore::Release();
}

::SE Sound::CreateSE(char* fileName){
	std::shared_ptr<SourceVoice> voice;
	voice.reset(Decode(fileName));

	::SE se;
	se.reset(new SE(voice,submixSE.get()));

	return se;
}

::BGM Sound::CreateBGM(char* fileName){
	std::shared_ptr<SourceVoice> voice;
	voice.reset(new SourceVoice(DecodeWave(fileName)));

	::BGM bgm;
	bgm.reset(new BGM(voice,submixBGM.get()));

	return bgm;
}

void Sound::SetBGMVolumes(float volume){
	submixBGM->SetVolume(volume);
}

void Sound::SetSEVolumes(float volume){
	submixSE->SetVolume(volume);
}

void Sound::SetAllVolume(float volume){
	SoundCore::GetMasteringVoice().SetVolume(volume);
}

Sound::SourceVoice* Decode(char* fileName){
	return new Sound::SourceVoice(Sound::DecodeWave(fileName),&(*Sound::submixSE));
}