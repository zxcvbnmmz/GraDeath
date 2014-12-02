#include "D2D/Sprite/Sprite.h"
#include "Scene/ResultScene.h"

#include "Scene/Factory/CharacterSelectFactory.h"
#include "Input/Gamepad.h"
#include "Input\Keyboard.h"
ResultScene::ResultScene(){
	s1st.Create(L"Resource/Scene/Result/1st.png");
	s2nd.Create(L"Resource/Scene/Result/2nd.png");
	s3rd.Create(L"Resource/Scene/Result/3rd.png");
	s4th.Create(L"Resource/Scene/Result/4th.png");

	pos_1st = D3DXVECTOR2(1000, 100);
	pos_2nd = D3DXVECTOR2(800, 200);
	pos_3rd = D3DXVECTOR2(600, 300);
	pos_4th = D3DXVECTOR2(400, 400);
}

SCENE_STATUS ResultScene::Execute(){

	/*if (GamePad::getAnyGamePadPressed(BUTTON_B) ||
#ifdef _DEBUG
		Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH){
#endif
		CharacterSelectFactory cf;
		SceneFactory::Reserve(&cf);
		return END_PROCESS;
	}
*/

	return STILL_PROCESSING;
}

void ResultScene::Draw(){
	s1st.SetPosition(pos_1st);
	s2nd.SetPosition(pos_2nd);
	s3rd.SetPosition(pos_3rd);
	s4th.SetPosition(pos_4th);

	s1st.Draw();
	s2nd.Draw();
	s3rd.Draw();
	s4th.Draw();
}
