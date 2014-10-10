#ifndef _INDEX_BUFFER_H__
#define _INDEX_BUFFER_H__

#include "Graphic/Buffer/Buffer.h"

class IndexBuffer : public Buffer{
public:
	bool Create(unsigned int numIndex, unsigned int size,void* data);
	void SetToIA();

private:
};

#endif	// end of IndexBuffer