#include "Shader/Shader.h"
#include "System/D3DCore.h"
#include "Graphic/D3DGraphic.h"

int CreateVertexShader(ID3D10Blob* compiledShader, ID3D10VertexShader** vertexBuffer);
int CreatePixelShader(ID3D10Blob* compiledShader, ID3D10PixelShader** pixelShader);

Shader::Shader() :compiledShader(nullptr), vertexShader(nullptr), pixelShader(nullptr), vertexLayout(nullptr){}

Shader::~Shader(){
	if (compiledShader){
		compiledShader->Release();
		compiledShader = nullptr;
	}
	if (vertexShader){
		vertexShader->Release();
		vertexShader = nullptr;
	}
	if (vertexLayout){
		vertexLayout->Release();
		vertexLayout = nullptr;
	}
	if (pixelShader){
		pixelShader->Release();
		pixelShader = nullptr;
	}
}

bool Shader::Compile(LPCWSTR fileName, const char* function, const char* profile){
	HRESULT hr;
	ID3D10Blob* err;
	char* str;

	if (FAILED(hr = D3DX10CompileFromFile(fileName, NULL, NULL, (LPCSTR)function, (LPCSTR)profile, D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &compiledShader, &err, NULL))){
		str = (char*)err->GetBufferPointer();

		MessageBox(NULL, L"hlsl�ǂݍ��ݎ��s", L"�G���[", MB_OK);
		return 0;
	}
	return 1;
}

bool Shader::CreateFromPrecompiledShader(const SHADER_STATUS& status){
	ID3D10Device* device = D3DCore::GetD3DDevice();
	if (FAILED(device->CreateVertexShader(status.vs, status.vsSize, &vertexShader))){
		return false;
	}

	if (FAILED(device->CreateInputLayout(status.layout, status.numElement, status.vs, status.vsSize, &vertexLayout))){
		return false;
	}

	if (FAILED(device->CreatePixelShader(status.ps, status.psSize, &pixelShader))){
		return false;
	}

	return true;
}

int Shader::CreateLayout(const D3D10_INPUT_ELEMENT_DESC* layout, UINT numElements){
	if (!layout){
		MessageBox(NULL, L"���_���C�A�E�g����ł�", L"�G���[", MB_OK);
	}

	if (FAILED(D3DCore::GetD3DDevice()->CreateInputLayout(layout, numElements, compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), &vertexLayout))){
		MessageBox(NULL, L"���_���C�A�E�g�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return 0;
	}

	return 1;
}

int CreateVertexShader(ID3D10Blob* compiledShader, ID3D10VertexShader** vertexShader){
	if (FAILED(D3DCore::GetD3DDevice()->CreateVertexShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), vertexShader))){
		if (compiledShader){
			compiledShader->Release();
			compiledShader = nullptr;
		}
		MessageBox(NULL, L"�o�[�e�b�N�X�V�F�[�_�[�쐬���s", L"�G���[", MB_OK);
		return 0;
	}
	return 1;
}

int CreatePixelShader(ID3D10Blob* compiledShader, ID3D10PixelShader** pixelShader){
	if (FAILED(D3DCore::GetD3DDevice()->CreatePixelShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), pixelShader))){
		if (compiledShader){
			compiledShader->Release();
			compiledShader = nullptr;
		}
		MessageBox(NULL, L"�s�N�Z���V�F�[�_�[�쐬���s", L"�G���[", MB_OK);
		return 0;
	}

	return 1;
}

void Shader::SetShaderLayout(){
	Graphic::D3D::VS::SetShader(vertexShader);
	Graphic::D3D::PS::SetShader(pixelShader);
	Graphic::D3D::IA::SetLayout(vertexLayout);
}