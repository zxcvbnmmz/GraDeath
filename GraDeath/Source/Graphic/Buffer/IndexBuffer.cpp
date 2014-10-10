#include "System/D3DCore.h"
#include "Graphic/D3DGraphic.h"
#include "Graphic/Buffer/IndexBuffer.h"

bool IndexBuffer::Create(unsigned int numIndex, unsigned int size,void* _data){
	D3D10_BUFFER_DESC bd;
	bd.Usage			= D3D10_USAGE_DEFAULT;
	bd.ByteWidth		= numIndex*size;
	bd.BindFlags		= D3D10_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags	= 0;
	bd.MiscFlags		= 0;

	D3D10_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = _data;
	InitData.SysMemPitch=0;
	InitData.SysMemSlicePitch=0;

	if( FAILED( D3DCore::GetD3DDevice()->CreateBuffer( &bd, &InitData, &buffer))){
		return false;
	}

	return true;
}

void IndexBuffer::SetToIA(){
	Graphic::D3D::IA::SetIndexBuffer(buffer,DXGI_FORMAT_R32_UINT,0);
}