#ifndef _CONSTANT_BUFFER_H__
#define _CONSTANT_BUFFER_H__

#include "Graphic/Buffer/Buffer.h"

class ConstantBuffer : public Buffer{
public:
	bool Create(unsigned int size);
	void SetToShader(unsigned int slot = 0);
	bool Map(D3D10_MAP mapType, unsigned int mapFlag, void** data);
	bool Map(void** data, D3D10_MAP mapType = D3D10_MAP_WRITE_DISCARD, unsigned int mapFlag = 0);
	void Unmap();
	
private:

};

#endif	// end of ConstantBuffer