#ifndef _WAVE_DATA_H__
#define _WAVE_DATA_H__

#include <D3DX10.h>
namespace Sound{
struct WaveData{
	WaveData():wfex(nullptr),waveBuffer(nullptr){}
	~WaveData(){delete[] wfex; delete[] waveBuffer;}

	WAVEFORMATEX* wfex;
	DWORD waveSize;
	BYTE* waveBuffer;
};
}
#endif	// end of WaveData