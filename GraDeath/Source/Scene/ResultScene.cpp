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

	for (int i = 0; i < 4; i++) {
		pos_rank[i] = D3DXVECTOR2(550 - i * 150, 100 + 100 * i);
		move_rank[i] = D3DXVECTOR2(0, 300);
		alpha[i] = 1.f;
	}
	timer = 0;
}

SCENE_STATUS ResultScene::Execute(){

//	if (GamePad::getAnyGamePadPressed(BUTTON_B) ||
//#ifdef _DEBUG
//		Keyboard::CheckKey(KC_S) == INPUT_PUSH){
//#endif
//		CharacterSelectFactory cf;
//		SceneFactory::Reserve(&cf);
//		return END_PROCESS;
//	}

	if (GamePad::getAnyGamePadPressed(BUTTON_A) ||
		GamePad::getAnyGamePadPressed(BUTTON_START)
#ifdef _DEBUG
		||
		Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH
#endif
		) {
		timer = 90;
	}

	for (int i = 0; i < 4; i++){
		if (timer > 30 + 15 * (3 - i))
		{
			move_rank[i].y *= .9f;
			alpha[i] *= .9f;
		}
	}
	timer++;
	return STILL_PROCESSING;
}

void ResultScene::Draw(){
	for (int i = 0; i < 4; i++){
		sRank[i].SetPosition(pos_rank[i] + move_rank[i]);
		sRank[i].SetAlpha(1.f - alpha[i]);
		sRank[i].Draw();
	}
}
