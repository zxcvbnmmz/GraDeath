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
	//CREATE(C);	// �G���[�ICREATE(class T)�Ɏw��ł���̂�Ref���p�������N���X����
};

INT WINAPI WinMain(HINSTANCE inst, HINSTANCE, LPSTR, INT){
#ifdef _DEBUG
	::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif

	A* a = A::Create();
	B* b = B::Create();
	auto a2 = A::Create();
	auto* b2 = B::Create();
	//auto& b = B::Create();	// �G���[

	// ObjectPoolManager�̓V���O���g��
	ObjectPoolManager* manager = ObjectPoolManager::GetInstance();
	// ObjectPoolManager��ObjectPool�������������Ă���
	ObjectPool* pool = manager->GetCurrentPool();
	// �v�[���̒��ɃI�u�W�F�N�g�����݂��邩�ǂ����m���߂���
	bool contain = pool->IsContains(a);
	// �v�[���̒��̃I�u�W�F�N�g���������Ƃ��o����
	pool->Erase(a);
	// �v�[���̒��̃I�u�W�F�N�g��S�ď������Ƃ��o����
	pool->Clear();
	// �S�v�[�����ɃI�u�W�F�N�g�����邩�T����
	contain = manager->IsObjectInPool(b);
	// �S�v�[�����̃I�u�W�F�N�g�ƃv�[��������
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