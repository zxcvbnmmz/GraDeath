#ifndef _BUFFER_H__
#define _BUFFER_H__

struct ID3D10Buffer;

class Buffer{
public:
	Buffer();
	virtual ~Buffer();
	ID3D10Buffer** GetBuffer();

protected:
	ID3D10Buffer* buffer;
};

inline ID3D10Buffer** Buffer::GetBuffer(){
	return &buffer;
}

#endif	// end of Buffer