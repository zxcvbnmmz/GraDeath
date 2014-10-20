#ifndef _SHADER_H__
#define _SHADER_H__

#include <D3D10_1.h>
#include <D3DX10math.h>

struct SHADER_STATUS{
	const BYTE* vs;
	size_t vsSize;
	const BYTE* ps;
	size_t psSize;
	D3D10_INPUT_ELEMENT_DESC* layout;
	unsigned int numElement;
};

struct ConstantDataBase{
	virtual ~ConstantDataBase(){}
};

class Shader{
public:
	Shader();
	virtual ~Shader();

	virtual void SetParameters(ConstantDataBase*) = 0;
	virtual HRESULT Compile() = 0;

protected:
	bool CreateFromPrecompiledShader(const SHADER_STATUS& status);
	void SetShaderLayout();

private:
	Shader(const Shader&);
	Shader& operator=(const Shader&);

	bool Compile(LPCWSTR fileName, const char* function, const char* profile);
	int CreateLayout(const D3D10_INPUT_ELEMENT_DESC* layout, UINT numElements);

	ID3D10Blob* compiledShader;
	ID3D10InputLayout* vertexLayout;
	ID3D10VertexShader* vertexShader;
	ID3D10PixelShader* pixelShader;
};

#endif	// end of Shader