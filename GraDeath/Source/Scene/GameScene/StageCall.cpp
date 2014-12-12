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
	// �t�@�C�����ƃR�[���o�b�N���w��
	se = Sound::CreateSE("", &stageCallBack);
}

void StageCall::Initialize(){
}

void StageCall::Release(){
}

int StageCall::Update(){
	// ���삪�I��������FINISHED��Ԃ��퓬�Ɉڍs����
	return FINISHED;

	// ���삪�܂������̂Ȃ�CALLING��Ԃ�
	return CALLING;
}

void StageCall::Draw(){

}
