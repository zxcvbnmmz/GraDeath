#include <Windows.h>
#include "Input\Keyboard.h"

namespace Input{
	//extern INPUT_STATE inputState[2][2];
	INPUT_STATE inputState[2][2] = {
		{ INPUT_FREE, INPUT_RELEASE },
		{ INPUT_PUSH, INPUT_PRESS }
	};
}

using namespace Input;

namespace{
	BYTE key[256] = { 0 };
	BYTE oldkey[256] = { 0 };
}

int Keyboard::Update(){
	memcpy(oldkey, key, 256);
	GetKeyboardState(key);

	return 1;
}

INPUT_STATE Keyboard::CheckKey(KEY_CODE keycode){
	int now = (key[keycode] & 0x80) >> 7;
	int old = (oldkey[keycode] & 0x80) >> 7;
	return inputState[now][old];
}

