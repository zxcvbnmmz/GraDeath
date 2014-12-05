#ifndef _SOUND_CALL_BACK_H__
#define _SOUND_CALL_BACK_H__

#include <XAudio2.h>

#define SOUND_CALLBACK(STRUCT) struct STRUCT : public IXAudio2VoiceCallback {	\
	STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired);	\
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS);							\
	STDMETHOD_(void, OnStreamEnd) (THIS);										\
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext);				\
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext);					\
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext);					\
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error);	\
};																		

#endif	// end of SoundCallBack