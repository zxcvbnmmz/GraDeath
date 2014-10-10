#ifndef _VERTEX_BUFFER_H__
#define _VERTEX_BUFFER_H__

#include "Buffer.h"

class VertexBuffer : public Buffer{
public:
	bool Create(unsigned int numVertex, unsigned int size,void* data);
	void SetToIA();
	unsigned int VertexBuffer::GetDataNum();

private:
	unsigned int dataNum;
	unsigned int dataSize;
};

inline unsigned int VertexBuffer::GetDataNum(){
	return dataNum;
}

#endif	// end of VertexBuffer