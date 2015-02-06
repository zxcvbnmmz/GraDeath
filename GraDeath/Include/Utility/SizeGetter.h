//--------------------------------------------
// @filename	SizeGetter.h
// @outline		�摜�T�C�Y�擾�֐�
// @auther		���c
//--------------------------------------------

//--------------------------------------------
// �C���N���[�h�K�[�h
//--------------------------------------------
#ifndef _SIZE_GETTER_H__
#define _SIZE_GETTER_H__

//--------------------------------------------
// �C���N���[�h
//--------------------------------------------
#include <D3DX10.h>

//--------------------------------------------
// @name
//  GetTextureSize(const char* fileName, D3DXVECTOR2* size)
// @param
//  const char* fileName	
//  D3DXVECTOR2* size		�e�N�X�`���T�C�Y�̊i�[��
// @todo
//  �e�N�X�`���̃T�C�Y���擾���i�[����
//--------------------------------------------
extern void GetTextureSize(LPCWSTR fileName, D3DXVECTOR2*);

#endif	// end of SizeGetter