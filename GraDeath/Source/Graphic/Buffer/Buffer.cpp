#include "System/D3DCore.h"
#include "Graphic/Buffer/Buffer.h"

Buffer::Buffer(){}

Buffer::~Buffer(){
	if(buffer){
		buffer->Release();
		buffer = nullptr;
	}
}