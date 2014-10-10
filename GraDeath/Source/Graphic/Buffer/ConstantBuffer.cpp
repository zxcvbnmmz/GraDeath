#include "System/D3DCore.h"
#include "Graphic/D3DGraphic.h"
#include "Graphic/Buffer/ConstantBuffer.h"

bool ConstantBuffer::Create(unsigned int size){
	D3D10_BUFFER_DESC cb;
	cb.BindFlags= D3D10_BIND_CONSTANT_BUFFER;
	cb.ByteWidth= size;
	cb.CPUAccessFlags=D3D10_CPU_ACCESS_WRITE;
	cb.MiscFlags =0;
	cb.Usage=D3D10_USAGE_DYNAMIC;

	if(FAILED(D3DCore::GetD3DDevice()->CreateBuffer( &cb,NULL,&buffer))){
		return false;
	}

	return true;
}

void ConstantBuffer::SetToShader(unsigned int slot){
	Graphic::D3D::VS::SetConstantBuffer(slot,1,&buffer);
	Graphic::D3D::PS::SetConstantBuffer(slot,1,&buffer);
}

bool ConstantBuffer::Map(D3D10_MAP mapType, unsigned int mapFlag, void** data){
	if(FAILED(buffer->Map(mapType,mapFlag,data))){
		return false;
	}
	return true;
}

bool ConstantBuffer::Map(void** data, D3D10_MAP mapType, unsigned int mapFlag){
	if(FAILED(buffer->Map(mapType,mapFlag,data))){
		return false;
	}
	return true;
}

void ConstantBuffer::Unmap(){
	buffer->Unmap();
}