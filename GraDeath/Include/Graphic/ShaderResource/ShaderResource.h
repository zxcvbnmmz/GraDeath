#ifndef _SHADER_RESOURCE_H__
#define _SHADER_RESOURCE_H__

#include <atlbase.h>

struct ID3D10ShaderResourceView;

namespace Graphic{
class ShaderResource{
public:
	ShaderResource();
	ShaderResource(LPCWSTR fiieName);
	ShaderResource(const char* fiieName);
	ShaderResource(CComPtr<ID3D10ShaderResourceView> _texture);
	~ShaderResource();

	void Release();
	void SetToShader(unsigned int slot=0, unsigned int numView = 1);
	bool Create(LPCWSTR fileName);
	bool Create(const char* fileName);
	void Create(CComPtr<ID3D10ShaderResourceView> _texture);
	bool IsValid();

private:
	CComPtr<ID3D10ShaderResourceView> texture;
};

inline bool ShaderResource::IsValid(){
	return texture.p != nullptr ? true : false;
}
}

#endif	// end of ShaderResource