#ifndef _SWAP_CHAIN_H__
#define _SWAP_CHAIN_H__

#include <atlcomcli.h>

struct ID3D10Device1;
struct DXGI_SWAP_CHAIN_DESC;
struct IDXGISwapChain;

namespace D3D{
class SwapChain{
public:
	static bool GetBuffer(unsigned int buffer, const IID& riid, void** surface);
	static IDXGISwapChain* GetSwapChain();
	static void Present(UINT syncInterval = 0, UINT flag = 0);
	static void GetDesc(DXGI_SWAP_CHAIN_DESC* desc);

private:
	friend class Device;
	static bool Create(CComPtr<ID3D10Device1> _device);
	static void Release();
};
}

#endif	// end of SwapChain