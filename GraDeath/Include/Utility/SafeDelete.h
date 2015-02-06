// ************************************************************
// filename	SafeDelete.h
// brief	�C���X�^���X�̈��S����E�j��
// name		����@�T
// note
// 2014.08.26
// ************************************************************

#ifndef _SAFE_DELETE_H_
#define _SAFE_DELETE_H_


namespace Util
{

// ************************************************************
// �C���X�^���X�̈��S���
// input : instance	- �C���X�^���X
// ************************************************************
template < class T > inline void safeDelete ( T& instance )
{
	if ( instance )
	{
		delete ( instance );
		( instance ) = nullptr;
	}
	return;
}

// ************************************************************
// �C���X�^���X�̈��S����@�z���
// input : instance	- �C���X�^���X
// ************************************************************
template < class T > inline void safeDeleteArray ( T& instance )
{
	if ( instance )
	{
		delete[ ] ( instance );
		( instance ) = nullptr;
	}
	return;
}

// ************************************************************
// SafeRelease : �V���O���|�C���^��
// input : instance	- �C���X�^���X
// ************************************************************
template < class T > inline void safeRelease ( T* instance )
{
	if ( instance )
	{
		( instance )->Release ();
		( instance ) = nullptr;
	}
}

// ************************************************************
// SafeRelease : �_�u���|�C���^��
// input : instance	- �C���X�^���X
// ************************************************************
template< class T > inline void safeRelease ( T **instance )
{
	if ( *instance != nullptr )
	{
		( *instance )->Release ();
		( *instance ) = nullptr;
	}
	return;
}

}

#endif