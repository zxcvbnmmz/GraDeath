#include "Scene/GameScene/StageCall.h"
#include "Sound/SoundCallBack.h"

SOUND_CALLBACK(STAGE_CALL);

void STAGE_CALL::OnVoiceProcessingPassStart(UINT32 BytesRequired){}
void STAGE_CALL::OnVoiceProcessingPassEnd(){}
void STAGE_CALL::OnStreamEnd(){}
void STAGE_CALL::OnBufferStart(void* pBufferContext){}
void STAGE_CALL::OnBufferEnd(void* pBufferContext){}
void STAGE_CALL::OnLoopEnd(void* pBufferContext){}
void STAGE_CALL::OnVoiceError(void* pBufferContext, HRESULT Error){}

namespace{
	STAGE_CALL stageCallBack;
}

StageCall::StageCall(){
	// ファイル名とコールバックを指定
	se = Sound::CreateSE("", &stageCallBack);
}

void StageCall::Initialize(){
}

void StageCall::Release(){
}

int StageCall::Update(){
	// 動作が終了したらFINISHEDを返し戦闘に移行する
	return FINISHED;

	// 動作がまだ続くのならCALLINGを返す
	return CALLING;
}

void StageCall::Draw(){

}
