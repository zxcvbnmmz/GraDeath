#ifdef _MSC_VER
#	define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#	define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 1
#endif

#include <crtdbg.h>
#include "System/System.h"
#include "Graphic/Graphic.h"
#include "Scene/SceneManager.h"
#include "Utility/Debug.h"

#include "Effect/Effect.h"
#include "Pool/ObjectPool.h"

struct A : public Ref{
	CREATE(A);
};

struct B : public A{
	CREATE(B);
};

struct C{
	//CREATE(C);	// エラー！CREATE(class T)に指定できるのはRefを継承したクラスだけ
};

INT WINAPI WinMain(HINSTANCE inst, HINSTANCE, LPSTR, INT){
#ifdef _DEBUG
	::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif

	A* a = A::Create();
	B* b = B::Create();
	auto a2 = A::Create();
	auto* b2 = B::Create();
	//auto& b = B::Create();	// エラー

	// ObjectPoolManagerはシングルトン
	ObjectPoolManager* manager = ObjectPoolManager::GetInstance();
	// ObjectPoolManagerはObjectPoolをいくつか持っている
	ObjectPool* pool = manager->GetCurrentPool();
	// プールの中にオブジェクトが存在するかどうか確かめられる
	bool contain = pool->IsContains(a);
	// プールの中のオブジェクトを消すことが出来る
	pool->Erase(a);
	// プールの中のオブジェクトを全て消すことが出来る
	pool->Clear();
	// 全プール内にオブジェクトがあるか探せる
	contain = manager->IsObjectInPool(b);
	// 全プール内のオブジェクトとプールを消す
	ObjectPoolManager::Destroy();

	if (!System::Initialize(inst)){
		return 0;
	}

	SceneManager::Initialize();

	while (System::Loop()){
		Graphic::Clear();

		if (!SceneManager::Execute()){
			break;
		}

		Graphic::Present(0, 0);
	}

	SceneManager::Release();

	System::Release();

	return 1;
}