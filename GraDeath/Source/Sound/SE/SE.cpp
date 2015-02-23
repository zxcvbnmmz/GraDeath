#include <XAudio2.h>
#include "Sound/SE/SE.h"
#include "Sound/Voice/SourceVoice.h"

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
		void SetLoop(unsigned int loopBegin, unsigned int loopEnd, unsigned int loopCount);
		void ExitLoop();
		bool IsEnable();

	private:
		std::shared_ptr<class SourceVoice> sourceVoice;
		unsigned int loopBegin = 0;
		unsigned int loopLength = 0;
		unsigned int loopCount = 0;
	};


	SE::SEPimpl::SEPimpl(std::shared_ptr<class SourceVoice> _sourceVoice, SubmixVoice* submix) :sourceVoice(_sourceVoice){}

	SE::SEPimpl::~SEPimpl(){
		Stop();
	}

	bool SE::SEPimpl::Play(bool cueing){
		if (cueing){
			Stop();
		}

		if (FAILED((*sourceVoice)->Start(0, XAUDIO2_COMMIT_NOW))){
			return false;
		}
		return true;
	}

	void SE::SEPimpl::Stop(){
		(*sourceVoice)->Stop();
		sourceVoice->SubmitBuffer(loopBegin, loopLength, loopCount);
	}

	void SE::SEPimpl::Pause(){
		(*sourceVoice)->Stop();
	}

	void SE::SEPimpl::SetVolume(float volume){
		(*sourceVoice)->SetVolume(volume);
	}

	void SE::SEPimpl::SetPitch(float pitch){
		(*sourceVoice)->SetFrequencyRatio(pitch);
	}

	float SE::SEPimpl::GetPlayingTime(){
		return sourceVoice->GetPlayingTime();
	}

	void SE::SEPimpl::SetLoop(unsigned int _loopBegin, unsigned int _loopLength, unsigned int _loopCount){
		loopBegin = _loopBegin;
		loopLength = _loopLength;
		loopCount = _loopCount;
		sourceVoice->SubmitBuffer(loopBegin, loopLength, loopCount);
	}

	bool SE::SEPimpl::IsEnable(){
		return sourceVoice != nullptr;
	}

	SE::SE(std::shared_ptr<class SourceVoice> _sourceVoice, SubmixVoice* submix):pimpl(new SEPimpl(_sourceVoice)){}

	SE::~SE(){
		Release();
	}

	void SE::Release(){
		if (pimpl){
			delete pimpl;
			pimpl = nullptr;
		}
	}

	bool SE::Play(bool cueing){
		return pimpl->Play(cueing);
	}

	void SE::Pause(){
		pimpl->Pause();
	}

	void SE::Stop(){
		pimpl->Stop();
	}

	void SE::SetVoume(float volume){
		pimpl->SetVolume(volume);
	}

	void SE::SetPitch(float pitch){
		pimpl->SetPitch(pitch);
	}

	float SE::GetPlayingTime(){
		return pimpl->GetPlayingTime();
	}

	void SE::SetLoop(unsigned int loopBegin, unsigned int loopEnd, unsigned int loopCount){
		pimpl->SetLoop(loopBegin, loopEnd, loopCount);
	}

	bool SE::IsEnable(){
		return pimpl->IsEnable();
	}
}
