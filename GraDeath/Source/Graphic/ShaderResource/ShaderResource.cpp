#include "Graphic/D3DGraphic.h"
#include "Graphic/ShaderResource/ShaderResource.h"
#include "Utility/Converter.h"

using namespace Graphic;

ShaderResource::ShaderResource():texture(nullptr){}

ShaderResource::ShaderResource(LPCWSTR fileName):texture(nullptr){
	Create(fileName);
}

ShaderResource::ShaderResource(const char* fileName):texture(nullptr){
	Create(fileName);
}

ShaderResource::ShaderResource(CComPtr<ID3D10ShaderResourceView> _texture):texture(_texture){}

ShaderResource::~ShaderResource(){}

void ShaderResource::SetToShader(unsigned int slot, unsigned int numView){
	Graphic::D3D::PS::SetShaderResource(slot,numView,&texture.p);
}

bool ShaderResource::Create(LPCWSTR fileName){
	if(texture){
		return false;
	}

	if(FAILED(Graphic::D3D::CreateShaderResourceView(&texture,fileName))){
		WCHAR* ext[5] = {L".bmp",L".png",L".jpg"};
		for(int i=0; i<3; ++i){
			WCHAR str[80];
			wcscpy_s(str,fileName);
			WCHAR* name = wcscat(wcstok(str,L"."),ext[i]);
			if(SUCCEEDED(Graphic::D3D::CreateShaderResourceView(&texture,name))){
				return true;
			}
		}

		MessageBox(NULL,L"テクスチャの読み込みに失敗\n拡張子が「jpg」「png」「bmp」以外か\nファイルサイズが大きすぎる可能性があるよ",
					L"読み込みエラー",MB_OK);
		return false;
	}

	return true;
}

bool ShaderResource::Create(const char* fileName){
	WCHAR str[80];
	return Create(Utility::ConvertToWChar(str,fileName));
}


void ShaderResource::Create(CComPtr<ID3D10ShaderResourceView> _texture){
	texture = _texture;
}
