#ifndef _SOUND_DECODER_H__
#define _SOUND_DECODER_H__

#include <memory>
namespace Sound{
std::shared_ptr<struct WaveData> DecodeWave(char* fileName);
}
#endif	// end of SoundDecoder