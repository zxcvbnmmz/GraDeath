#include "Scene/GameScene/StageCall.h"
#include "Sound/SoundCallBack.h"
#include "Input\Keyboard.h"

namespace{
	SOUND_CALLBACK(STAGE_CALL);
	int endFlg;

	void STAGE_CALL::OnVoiceProcessingPassStart(UINT32 BytesRequired){}
	void STAGE_CALL::OnVoiceProcessingPassEnd(){}
	void STAGE_CALL::OnStreamEnd(){ endFlg = 1; }
	void STAGE_CALL::OnBufferStart(void* pBufferContext){}
	void STAGE_CALL::OnBufferEnd(void* pBufferContext){}
	void STAGE_CALL::OnLoopEnd(void* pBufferContext){}
	void STAGE_CALL::OnVoiceError(void* pBufferContext, HRESULT Error){}

	STAGE_CALL stageCallBack;
	STAGE_CALL endCallBack;
}

StageCall::StageCall(){
	// ファイル名とコールバックを指定
	startSE = Sound::CreateSE("Resource/Scene/Game/StageCall/startSE.wav", &stageCallBack);
	endSE = Sound::CreateSE("Resource/Scene/Game/StageCall/endSE.wav", &endCallBack);
	readyText.Create(L"Resource/Scene/Game/StageCall/ReadyText.png");
	startText.Create(L"Resource/Scene/Game/StageCall/CallText.png");
	endText.Create(L"Resource/Scene/Game/StageCall/EndText.png");

}

void StageCall::Initialize(bool pIsEndCall){
	isEndCall = pIsEndCall;
	switch (isEndCall){
	case false:
		startSE->Play();
		break;
	default:
		endSE->Play();
		startSE->Stop();
		break;
	}

	text_pos = D3DXVECTOR2(200, 200);
	text_move = D3DXVECTOR2(1600, 0);

	cTimer = 0;
	callFlg = false;
	endFlg = 0;
}

void StageCall::Release(){
	startSE->Release();
	endSE->Release();
	startText.Release();
	endText.Release();
}

void StageCall::Draw(){
	switch (isEndCall)
	{
	case false:
		if (text_move.x <= 0){
			startText.SetPosition(text_pos + text_move);
			startText.Draw();
		}
		else{
			readyText.SetPosition(text_pos + text_move);
			readyText.Draw();
		}
		break;
	default:
		endText.SetPosition(text_pos + text_move);
		endText.Draw();
		break;
	}
}

int StageCall::Update(){
#ifndef _DEBUG
	if (Keyboard::CheckKey(KC_ENTER) == INPUT_PRESS)
	{
		// 動作が終了したらFINISHEDを返し戦闘に移行する
		return FINISHED;
	}
#endif
	switch (callFlg)
	{
	case false:
		text_move *= .97 - (.02 * isEndCall);
		break;
	default:
		text_move /= .90;
		break;
	}
	if (text_move.x < 1 && text_move.x > 0)
	{
		//cTimer = 30;
		callFlg = true;
		text_move = D3DXVECTOR2(-1, 0);
	}

	//if (text_move.x < -1000)
	//	return FINISHED;

	return endFlg;

	//if (cTimer-- < 0 && callFlg)
	//{
	//	text_move = D3DXVECTOR2(-1, 0);
	//}
	// 動作がまだ続くのならCALLINGを返す
	return CALLING;
}
