#ifndef _TEST_SHADER_H__
#define _TEST_SHADER_H__

#include "Shader/Shader.h"
#include <memory>
#include "Graphic/Buffer/ConstantBuffer.h"

struct TestDatas : public ConstantDataBase{
	struct GameData{
		D3DXVECTOR4 lightDir;
		D3DXVECTOR4 eye;
	}gameData;

	struct BufferData{
		D3DXMATRIX world;
		D3DXMATRIX wvp;
		D3DXVECTOR4 ambient;
		D3DXVECTOR4 diffuse;
		D3DXVECTOR4 specular;
		BufferData(){
			for (int i = 0; i<4; ++i){
				ambient[i] = 1;
				diffuse[i] = 1;
				specular[i] = 0;
			}
			D3DXMatrixIdentity(&world);
			D3DXMatrixIdentity(&wvp);
		}
	}bufferData;
};

class TestShader : public Shader{
public:
	TestShader();
	~TestShader();

	HRESULT Compile();
	void SetParameters(ConstantDataBase*);

private:
	ConstantBuffer buffer[2];
};

#endif	//	end of TestShader