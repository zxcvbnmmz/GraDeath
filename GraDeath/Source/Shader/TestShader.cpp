#include "Shader/TestShader.h"
#include "Graphic/Sampler/Sampler.h"

//#include "Resource/Shader/TestShadervso.h"
//#include "Resource/Shader/TestShaderpso.h"

TestShader::TestShader(){
}

TestShader::~TestShader(){

}

HRESULT TestShader::Compile(){
	buffer[1].Create(sizeof(TestDatas::BufferData));
	buffer[0].Create(sizeof(TestDatas::GameData));

	D3D10_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	SHADER_STATUS status;
	//SHADER_STATUS status = { g_VS, sizeof(g_VS), g_PS, sizeof(g_PS), layout, numElements };

	CreateFromPrecompiledShader(status);

	return S_OK;
}

void TestShader::SetParameters(ConstantDataBase* data){
	void* temp = data;
	TestDatas* tData = static_cast<TestDatas*>(data);


	TestDatas::GameData* gameData;
	if (buffer[0].Map((void**)&gameData)){
		gameData->eye = tData->gameData.eye;
		gameData->lightDir = tData->gameData.lightDir;
		buffer[0].Unmap();
	}

	TestDatas::BufferData* bufferData;
	if (buffer[1].Map((void**)&bufferData)){
		bufferData->ambient = tData->bufferData.ambient;
		bufferData->diffuse = tData->bufferData.diffuse;
		bufferData->specular = tData->bufferData.specular;
		bufferData->world = tData->bufferData.world;
		bufferData->wvp = tData->bufferData.wvp;
		D3DXMatrixTranspose(&bufferData->world, &bufferData->world);
		D3DXMatrixTranspose(&bufferData->wvp, &bufferData->wvp);

		buffer[1].Unmap();
	}

	// レイアウトとかサンプラとか渡す
	SetShaderLayout();

	// コンスタントバッファ渡す
	for (int i = 0; i<2; ++i){
		buffer[i].SetToShader(i);
	}

	// サンプラー渡す
	Sampler::SetPointWrap();
}