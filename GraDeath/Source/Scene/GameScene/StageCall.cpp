#include "Scene/GameScene/StageCall.h"
#include "Sound/SoundCallBack.h"
#include "Input\Keyboard.h"

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
	//se = Sound::CreateSE("", &stageCallBack);
	sCallText.Create(L"Resource/Scene/Game/StageCall/CallText.png");

	text_pos = D3DXVECTOR2(200, 200);
	text_move = D3DXVECTOR2(1600, 0);

	cTimer = 0;
	callFlg = false;
}

void StageCall::Initialize(){
}

void StageCall::Release(){
}

int StageCall::Update(){
	if (Keyboard::CheckKey(KC_ENTER) == INPUT_PRESS)
	{
		// 動作が終了したらFINISHEDを返し戦闘に移行する
		return FINISHED;
	}

	switch (callFlg)
	{
	case false:
		text_move *= .9;
		break;
	default:
		text_move /= .85;
		break;
	}
	if (text_move.x < 1 && text_move.x > 0)
	{
		//cTimer = 30;
		callFlg = true;
		text_move = D3DXVECTOR2(-1, 0);
	}

	if (text_move.x < -1000)
		return FINISHED;

	//if (cTimer-- < 0 && callFlg)
	//{
	//	text_move = D3DXVECTOR2(-1, 0);
	//}
	// 動作がまだ続くのならCALLINGを返す
	return CALLING;
}

void StageCall::Draw(){
	sCallText.SetPosition(text_pos + text_move);
	sCallText.Draw();
}
