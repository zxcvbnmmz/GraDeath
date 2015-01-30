// ************************************************************
// filename	PlayerManager.cpp
// brief	Playerの管理
// name		川口　裕
// note
// 2014.10.27
// ************************************************************

// インクルード ***********************************************
#include "ResourseManager/PlayerManager/PlayerManager.h"
#include "Object/Character.h"
#include "Utility/SafeDelete.h"
#include "CharacterController/CharacterController.h"
#include <vector>


#define CONTROLLER_SIZE ( 3 )

namespace PlayerManager
{
	namespace
	{
		std::vector< CharacterController* > controller;
	}

	// 初期化
	void Init ()
	{
		Release ();
		controller.resize ( CONTROLLER_SIZE );
		for ( int i = 0; i < CONTROLLER_SIZE; i++ )
			controller[ i ] = nullptr;
	}

	// 更新
	void Update ()
	{
		for ( int i = 0; i < CONTROLLER_SIZE; i++ )
		{
			if ( controller[ i ] == nullptr )
				controller[ i ]->Update ();
		}
	}

	// 描画
	void Draw ()
	{
		for ( int i = 0; i < CONTROLLER_SIZE; i++ )
		{
			if ( controller[ i ] == nullptr )
				controller[ i ]->Draw ();
		}
	}

	// 解放
	void Release ()
	{
		for ( int i = 0; i < CONTROLLER_SIZE; i++ )
		{
			Util::safeDelete ( controller[ i ] );
		}
		controller.clear ();
	}

	// コントローラーセット
	void SetController ( CharacterController* _controller )
	{
		controller.push_back ( _controller );
	}

}
