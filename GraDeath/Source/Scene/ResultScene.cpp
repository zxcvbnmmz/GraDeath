#include "D2D/Sprite/Sprite.h"
#include "Scene/ResultScene.h"

#include "Scene/Factory/CharacterSelectFactory.h"
#include "Input/Gamepad.h"
#include "Input\Keyboard.h"
ResultScene::ResultScene(){
	
	sRank[0].Create(L"Resource/Scene/Result/1st.png");
	sRank[1].Create(L"Resource/Scene/Result/2nd.png");
	sRank[2].Create(L"Resource/Scene/Result/3rd.png");
	sRank[3].Create(L"Resource/Scene/Result/4th.png");
	sPlayer[0].Create(L"Resource/Scene/Result/1p.png");
	sPlayer[1].Create(L"Resource/Scene/Result/2p.png");
	sPlayer[2].Create(L"Resource/Scene/Result/3p.png");
	sPlayer[3].Create(L"Resource/Scene/Result/4p.png");
	sChara[0].Create(L"Resource/Scene/Result/Chara1.png");
	sChara[1].Create(L"Resource/Scene/Result/Chara2.png");
	sChara[2].Create(L"Resource/Scene/Result/Chara3.png");
	sChara[3].Create(L"Resource/Scene/Result/Chara4.png");
	sFrame.Create(L"Resource/Scene/Result/Frame.png");
	for (int i = 0; i < 4; i++) {
		pRank[i] = D3DXVECTOR2(550 - i * 150, 100 + 100 * i);
		pMove[i] = D3DXVECTOR2(0, 300);
		alpha[i] = 1.f;
	}
	pChara = D3DXVECTOR2(0, 210);
	pPlayer = D3DXVECTOR2(0, 280);
	timer = 0;
}

SCENE_STATUS ResultScene::Execute(){

	if (GamePad::getAnyGamePadPressed(BUTTON_B) ||
#ifdef _DEBUG
		Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH){
#endif
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
		timer = 90;
	}

	for (int i = 0; i < 4; i++){
		if (timer > 30 + 15 * (3 - i))
		{
			pMove[i].y *= .9f;
			alpha[i] *= .9f;
		}
	}
	timer++;
	return STILL_PROCESSING;
}

void ResultScene::Draw(){
	for (int i = 0; i < 4; i++){
		sFrame.SetPosition(pRank[i] + pMove[i]);
		sFrame.SetAlpha(1.f - alpha[i]);
		sRank[i].SetPosition(pRank[i] + pMove[i]);
		sRank[i].SetAlpha(1.f - alpha[i]);
		sPlayer[i].SetPosition(pRank[i] + pMove[i] + pPlayer);
		sPlayer[i].SetAlpha(1.f - alpha[i]);
		sChara[i].SetPosition(pRank[i] + pMove[i] + pChara);
		sChara[i].SetAlpha(1.f - alpha[i]);

		sFrame.Draw();
		sRank[i].Draw();
		sChara[i].Draw();
		sPlayer[i].Draw();
	}
}
