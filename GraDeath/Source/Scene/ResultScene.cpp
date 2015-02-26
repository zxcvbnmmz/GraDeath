#include "D2D/Sprite/Sprite.h"
#include "Scene/ResultScene.h"

#include "CharacterController/CharacterInfo.h"
#include "Manager/HitPointManager.h"
#include "Scene/Factory/CharacterSelectFactory.h"
#include "Input/Gamepad.h"
#include "Input\Keyboard.h"
#include "Manager/BGMManager.h"

#include "Sound/SoundCallBack.h"

namespace{
	SOUND_CALLBACK(SE_CALL);
	void SE_CALL::OnVoiceProcessingPassStart(UINT32 BytesRequired){}
	void SE_CALL::OnVoiceProcessingPassEnd(){}
	void SE_CALL::OnStreamEnd(){ BGMManager::GetInstance()->Play("Resource/BGM/GDtitle.wav"); }
	void SE_CALL::OnBufferStart(void* pBufferContext){}
	void SE_CALL::OnBufferEnd(void* pBufferContext){}
	void SE_CALL::OnLoopEnd(void* pBufferContext){}
	void SE_CALL::OnVoiceError(void* pBufferContext, HRESULT Error){}

	SE_CALL seCallBack;
}

ResultScene::ResultScene(){
	
	//sRank[0].Create(L"Resource/Scene/Result/1st.png");
	sRank[1].Create(L"Resource/Scene/Result/2nd.png");
	sRank[2].Create(L"Resource/Scene/Result/3rd.png");
	sRank[3].Create(L"Resource/Scene/Result/4th.png");
	//sPlayer[0].Create(L"Resource/Scene/Result/1p.png");
	//sPlayer[1].Create(L"Resource/Scene/Result/2p.png");
	//sPlayer[2].Create(L"Resource/Scene/Result/3p.png");
	//sPlayer[3].Create(L"Resource/Scene/Result/4p.png");
	//sChara[0].Create(L"Resource/Scene/Result/Chara1.png");
	//sChara[1].Create(L"Resource/Scene/Result/Chara2.png");
	//sChara[2].Create(L"Resource/Scene/Result/Chara3.png");
	//sChara[3].Create(L"Resource/Scene/Result/Chara4.png");
	//BGMManager::GetInstance ()->Play ( "Resource/BGM/GDtitle.wav" );

	sBG.Create(L"Resource/Scene/Result/Result_bg.png");
	for (int i = 0; i < 4; i++) {
		int rank, chara;
		chara = HitPointManager::GetPlayerRanking(i, rank);
		if ( rank < 0 ){
			continue;
		}
		switch (chara)
		{
		case CharacterInfo::PLAYER_BLUE:
			if (rank != 1)
				sChara[rank - 1].Create(L"Resource/Scene/Result/Chara1.png");
			else{
				sChara[rank - 1].Create(L"Resource/Scene/Result/1st_B.png");
				vWin = Sound::CreateSE("Resource/Voice/chara2_win.wav");
			}
			break;
		case CharacterInfo::PLAYER_RED:
			if (rank != 1)
				sChara[rank - 1].Create(L"Resource/Scene/Result/Chara2.png");
			else{
				sChara[rank - 1].Create(L"Resource/Scene/Result/1st_R.png");
				vWin = Sound::CreateSE("Resource/Voice/chara1_win.wav");
			}
			break;
		case CharacterInfo::PLAYER_YELLOW:
			if (rank != 1)
				sChara[rank - 1].Create(L"Resource/Scene/Result/Chara3.png");
			else{
				sChara[rank - 1].Create(L"Resource/Scene/Result/1st_Y.png");
				vWin = Sound::CreateSE("Resource/Voice/chara3_win.wav");
			}
			break;
		case CharacterInfo::PLAYER_GRAY:
			if (rank != 1)
				sChara[rank - 1].Create(L"Resource/Scene/Result/Chara4.png");
			else{
				sChara[rank - 1].Create(L"Resource/Scene/Result/1st_WB.png");
				vWin = Sound::CreateSE("Resource/Voice/chara4_win.wav");
			}
			break;
		}
		switch (i)
		{
		case 0:
			if (rank != 1)
				sPlayer[rank - 1].Create(L"Resource/Scene/Result/1p.png");
			else
				sPlayer[rank - 1].Create(L"Resource/Scene/Result/1st_1p.png");
			break;
		case 1:
			if (rank != 1)
				sPlayer[rank - 1].Create(L"Resource/Scene/Result/2p.png");
			else
				sPlayer[rank - 1].Create(L"Resource/Scene/Result/1st_2p.png");
			break;
		case 2:
			if (rank != 1)
				sPlayer[rank - 1].Create(L"Resource/Scene/Result/3p.png");
			else
				sPlayer[rank - 1].Create(L"Resource/Scene/Result/1st_3p.png");
			break;
		case 3:
			if (rank != 1)
				sPlayer[rank - 1].Create(L"Resource/Scene/Result/4p.png");
			else
				sPlayer[rank - 1].Create(L"Resource/Scene/Result/1st_4p.png");
			break;
		}
		pRank[i] = D3DXVECTOR2(550 - i * 150, 100 + 100 * i);
		pMove[i] = D3DXVECTOR2(0, 300);
		alpha[i] = 1.f;
	}
	winSE = Sound::CreateSE("Resource/Scene/Result/winSE.wav", &seCallBack);
	pChara = D3DXVECTOR2(0, 210);
	pPlayer = D3DXVECTOR2(0, 280);
	timer = 0;
	bgm = Sound::CreateBGM("Resource/BGM/GDtitle.wav");
	winSE->Play();
}

SCENE_STATUS ResultScene::Execute(){

	if (GamePad::getAnyGamePadPressed(BUTTON_B)
#ifdef _DEBUG
		|| Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH
#endif
	){
		CharacterSelectFactory cf;
		SceneFactory::Reserve(&cf);
		return END_PROCESS;
	}

	if (GamePad::getAnyGamePadPressed(BUTTON_A) ||
		GamePad::getAnyGamePadPressed(BUTTON_START)
#ifdef _DEBUG
		||
		Keyboard::CheckKey(KC_S) == INPUT_PUSH
#endif
		) {
		timer = 300;
	}

	for (int i = 1; i < 4; i++){
		if (timer > 60 + 30 * (3 - i))
		{
			pMove[i].y *= .9f;
			alpha[i] *= .9f;
		}
	}
	if (timer > 200){
		pMove[0].y *= .98f;
		alpha[0] *= .98f;
	}
	if (timer > 300)
		vWin->Play();
	timer++;
	return STILL_PROCESSING;
}

void ResultScene::Draw(){
	sBG.SetPosition(0, 0);
	sBG.Draw();
	for (int i = 0; i < 4; i++){
		sPlayer[i].SetPosition(pRank[i] + pMove[i] + D3DXVECTOR2((i == 0) * 500, (i == 0) * 500));
		sPlayer[i].SetAlpha(1.f - alpha[i]);
		sChara[i].SetPosition(pRank[i] + pMove[i]);
		sChara[i].SetAlpha(1.f - alpha[i]);

		sChara[i].Draw();
		sPlayer[i].Draw();
		if (i != 0){
			sRank[i].SetPosition(pRank[i] + pMove[i]);
			sRank[i].SetAlpha(1.f - alpha[i]);
			sRank[i].Draw();
		}
	}
}
