#ifndef _DEVICE_H__
#define _DEVICE_H__

#include <atlcomcli.h>
#include <memory>

struct ID3D10Device1;

namespace D3D{
class Device{
public:
	static bool Create();
	static void Release();
	static CComPtr<ID3D10Device1> GetDevice();

private:
	class Pimpl;
	static std::shared_ptr<Pimpl> pimpl;
};

}

#endif	// end of Device