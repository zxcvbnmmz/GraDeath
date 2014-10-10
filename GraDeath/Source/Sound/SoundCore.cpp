#include "Sound/SoundCore.h"
#include <XAudio2.h>
#include "Sound/Voice/MasterVoice.h"
#include "Sound/Voice/SubmixVoice.h"

namespace SoundCore{
	struct Core{
		MasterVoice masterVoice;
		IXAudio2* xAudio;
	}core;
}

IXAudio2* SoundCore::GetXAudio(){
	return core.xAudio;
}

SoundCore::MasterVoice& SoundCore::GetMasteringVoice(){
	return core.masterVoice;
}

bool SoundCore::Initialize(){
	CoInitializeEx(NULL,COINIT_MULTITHREADED);	

	unsigned int flag = 0;
#ifdef _DEBUG
	flag |= XAUDIO2_DEBUG_ENGINE;
#endif

	HRESULT hr = XAudio2Create(&core.xAudio,flag);
	if(FAILED(hr)){
		MessageBox(NULL,L"XAudioの初期化に失敗",L"エラー",MB_OK);
		return false;
	}

	hr = core.xAudio->CreateMasteringVoice(&core.masterVoice);
	if(FAILED(hr)){
		MessageBox(NULL,L"マスターボイスの作成に失敗",L"エラー",MB_OK);
		return false;
	}

	return true;
}

void SoundCore::Release(){
	core.masterVoice.Release();

	if(core.xAudio){
		core.xAudio->Release();
		core.xAudio = nullptr;
	}
	CoUninitialize();
}