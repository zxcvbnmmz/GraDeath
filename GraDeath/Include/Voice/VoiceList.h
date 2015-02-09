#ifndef _VOICE_LIST_H__
#define _VOICE_LIST_H__

enum VOICE_LIST{
	VOICE_ATTACK,
	VOICE_SKILL1,
	VOICE_MAX,
};

static char* characterVoices[4][VOICE_MAX]{
	{
		"Resource/Sound/xxx",
		"Resource/Sound/xxx",
	},
	{
		"Resource/Sound/xxx",
		"Resource/Sound/xxx",
	},
};

#endif	// end of VoiceList