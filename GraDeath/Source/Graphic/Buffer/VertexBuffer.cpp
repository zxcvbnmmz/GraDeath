#include "System/D3DCore.h"
#include "Graphic/D3DGraphic.h"
#include "Graphic/Buffer/VertexBuffer.h"

bool VertexBuffer::Create(unsigned int numVertex, unsigned int size, void* _data){
	D3D10_BUFFER_DESC bd;
	bd.Usage			= D3D10_USAGE_DEFAULT;
	bd.ByteWidth		= numVertex*size;
	bd.BindFlags		= D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags	= 0;
	bd.MiscFlags		= 0;
	
	D3D10_SUBRESOURCE_DATA initData;
	initData.pSysMem = _data;

	if(FAILED(D3DCore::GetD3DDevice()->CreateBuffer(&bd,&initData,&buffer))){
		MessageBox(NULL,L"バッファの作成に失敗",L"エラー",MB_OK);
		return false;
	}

	dataNum = numVertex;
	dataSize = size;

	return true;
}

void VertexBuffer::SetToIA(){
	Graphic::D3D::IA::SetVertexBuffer(0,1,&buffer,dataSize,0);
}