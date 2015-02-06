#include "Utility/ScreenShot.h"
#include "System/D3DCore.h"
#include "D3D/SwapChain/SwapChain.h"
#include <Windows.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <d3dx10.h>

namespace Utility{

	TCHAR CreateTextureDirectory(LPCWSTR filePath, LPCWSTR fileHedderName, unsigned int maxFileIndex);
	void CreateTextureDirectory(LPCWSTR filePath, TCHAR* dstPath);
	bool SaveTexture(LPCWSTR filePath, LPCWSTR fileHedder, unsigned int maxFileIndex);

	bool CreateScreenShot(LPCWSTR filePath, unsigned int maxFileIndex){
		TCHAR directory[_MAX_PATH];
		CreateTextureDirectory(filePath, directory);
		return SaveTexture(directory, L"ScreenShot", maxFileIndex);
	}

	bool CreateScreenShot(LPCWSTR filePath, LPCWSTR fileHedderName, unsigned int maxFileIndex){
		TCHAR directory[_MAX_PATH];
		CreateTextureDirectory(filePath, directory);
		return SaveTexture(directory, fileHedderName, maxFileIndex);
	}

	void CreateTextureDirectory(LPCWSTR filePath, TCHAR* dstPath){
		TCHAR fileDir[_MAX_PATH];

		// �ۑ�����t�@�C���p�X���w�肳��Ă���΂�����g��
		if (wcscmp(filePath, L"")){
			wcscpy_s(fileDir, filePath);
		}
		// �w�肳��Ă��Ȃ� = �󂾂����ꍇ�A�K���ȏꏊ�ɍ��
		else{
			TCHAR moduleFilePath[_MAX_PATH];
			GetModuleFileName(0, moduleFilePath, _MAX_PATH);
			if (_tcsclen(moduleFilePath) > 3)
				*(_tcsrchr(moduleFilePath, _T('\\')) + 1) = _T('\0');
			wsprintf(fileDir, _T("%sScreenShot\\"), moduleFilePath);
		}

		// �t�@�C���p�X�̃f�B���N�g�������݂��Ȃ���΍��
		if (PathFileExists(fileDir) == false){
			CreateDirectory(fileDir, 0);
		}
		wcscpy_s(dstPath,_MAX_PATH, fileDir);
	}

	bool SaveTexture(LPCWSTR filePath, LPCWSTR fileHedder, unsigned int maxFileIndex){
		TCHAR dstFileName[_MAX_PATH];

		// ���ݕۑ�����Ă���X�N���[���V���b�g�̖����𐔂���
		// �w�肳�ꂽ�����ȏ�Ȃ�ۑ����Ȃ��悤�ɂ���
		// %s%s%03d�̓t�@�C���p�X+�t�@�C����+3���̎g���Ă��Ȃ��ԍ���A����������
		unsigned int n = 0;
		for (; n < maxFileIndex; ++n){
			wsprintf(dstFileName, _T("%s%s%03d.jpg"), filePath, fileHedder, n);
			if (PathFileExists(dstFileName) == false){
				break;
			}
		}

		if (n >= maxFileIndex){
			MessageBox(NULL, L"�X�N���[���V���b�g�̍쐬���I�[�o�[", L"�G���[", MB_OK);
			return false;
		}


		ID3D10Texture2D* backBuffer = nullptr;

		HRESULT hr;
		if (!D3D::SwapChain::GetBuffer(0, __uuidof(ID3D10Texture2D), (void**)&backBuffer)){
			return false;
		}

		DXGI_SWAP_CHAIN_DESC desc;
		D3D::SwapChain::GetDesc(&desc);
		if (desc.SampleDesc.Count == 1 && desc.SampleDesc.Quality == 0){
			D3DX10SaveTextureToFile(backBuffer, D3DX10_IFF_JPG, dstFileName);
		}
		else{
			ID3D10Texture2D* texture = nullptr;
			D3D10_TEXTURE2D_DESC texDesc;
			backBuffer->GetDesc(&texDesc);
			texDesc.Usage = D3D10_USAGE_DEFAULT;
			texDesc.SampleDesc.Count = 1;
			texDesc.SampleDesc.Quality = 0;
			hr = D3DCore::GetD3DDevice()->CreateTexture2D(&texDesc, NULL, &texture);
			if (FAILED(hr)){
				return false;
			}

			D3DCore::GetD3DDevice()->ResolveSubresource(texture, NULL, backBuffer, NULL, texDesc.Format);
			D3DX10SaveTextureToFile(texture, D3DX10_IFF_JPG, dstFileName);

			texture->Release();
			texture = nullptr;
		}

		backBuffer->Release();
		backBuffer = nullptr;

		return true;
	}
	
}
