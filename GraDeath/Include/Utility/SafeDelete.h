// ************************************************************
// filename	SafeDelete.h
// brief	インスタンスの安全解放・破棄
// name		川口　裕
// note
// 2014.08.26
// ************************************************************

#ifndef _SAFE_DELETE_H_
#define _SAFE_DELETE_H_


namespace Util
{

// ************************************************************
// インスタンスの安全解放
// input : instance	- インスタンス
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
// インスタンスの安全解放　配列版
// input : instance	- インスタンス
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
// SafeRelease : シングルポインタ版
// input : instance	- インスタンス
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
// SafeRelease : ダブルポインタ版
// input : instance	- インスタンス
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