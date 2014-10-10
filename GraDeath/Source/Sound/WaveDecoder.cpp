#include <D3DX10.h>
#include "Sound/WaveDecoder.h"
#include "Sound/WaveData.h"

Sound::WaveData* LoadFormat(HMMIO hMmio);
void Read(HMMIO hMmio, Sound::WaveData* wave);

namespace Sound{
std::shared_ptr<struct WaveData> DecodeWave(char* fileName){
	HMMIO hMmio = NULL;

	unsigned int flag = MMIO_ALLOCBUF;
#ifdef _DEBUG
	flag |= MMIO_READ;
#endif
	hMmio = mmioOpenA(fileName, NULL, flag);

	if(hMmio == NULL){
		return nullptr;
	}

	Sound::WaveData* waveData = LoadFormat(hMmio);
	Read(hMmio,waveData);

	mmioClose(hMmio,0);

	std::shared_ptr<Sound::WaveData> wave;
	wave.reset(waveData);

	return wave;
}
}

Sound::WaveData* LoadFormat(HMMIO hMmio){
	Sound::WaveData* wave = new Sound::WaveData;

	MMCKINFO riffCk,inCk;
	memset(&riffCk,0,sizeof(riffCk));
	memset(&inCk,0,sizeof(inCk));

	if(mmioDescend(hMmio,&riffCk,NULL,0) != 0){
		return nullptr;
	}

	if(riffCk.ckid != FOURCC_RIFF || riffCk.fccType != mmioFOURCC('W','A','V','E')){
		return nullptr;
	}

	inCk.ckid = mmioFOURCC('f','m','t',' ');
	if(mmioDescend(hMmio,&inCk,&riffCk,MMIO_FINDCHUNK) != 0){
		return nullptr;
	}

	if(inCk.cksize < sizeof(PCMWAVEFORMAT)){
		return nullptr;
	}

	PCMWAVEFORMAT pcmWaveFormat;
	if(mmioRead(hMmio,(HPSTR)&pcmWaveFormat,sizeof(pcmWaveFormat)) != inCk.cksize){
		return nullptr;
	}

	if(pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM){
		wave->wfex = (WAVEFORMATEX*)new char[sizeof(WAVEFORMATEX)];
		if(wave->wfex == NULL){
			return nullptr;
		}
		memcpy(wave->wfex,&pcmWaveFormat,sizeof(PCMWAVEFORMAT));
		wave->wfex->cbSize = 0;
	}else{
		return nullptr;
	}

	if(mmioAscend(hMmio,&inCk,0) != 0){
		return nullptr;
	}

	inCk.ckid = mmioFOURCC('d','a','t','a');

	if(mmioDescend(hMmio,&inCk,&riffCk,MMIO_FINDCHUNK) != 0){
		return nullptr;
	}

	wave->waveSize = inCk.cksize;
	wave->waveBuffer = new BYTE[wave->waveSize];

	return wave;
}

void Read(HMMIO hMmio, Sound::WaveData* wave){
	if(wave == nullptr){
		return;
	}
	
	MMIOINFO mmioinfoIn;

	if(mmioGetInfo(hMmio,&mmioinfoIn,0)!=0){
		return;
	}

	unsigned int dataIn = wave->waveSize;

	for(unsigned int i=0; i<dataIn; ++i){
		if(mmioinfoIn.pchNext == mmioinfoIn.pchEndRead){
			if(mmioAdvance(hMmio, &mmioinfoIn, MMIO_READ) != 0){
				return;
			}
			if(mmioinfoIn.pchNext == mmioinfoIn.pchEndRead){
				return;
			}
		}
		*(wave->waveBuffer+i) = *((BYTE*)mmioinfoIn.pchNext);
		++mmioinfoIn.pchNext;
	}
}
