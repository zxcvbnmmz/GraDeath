#ifndef _MACRO_H__
#define _MACRO_H__

// �֐��̎g�p���֎~����}�N��
// DEPRECATED void Func();
// �̂悤�ɏ����΁AFunc���Ă񂾉ӏ��ŃG���[���N����
#define DEPRECATED __declspec(deprecated)

// �C���X�^���X���쐬���I�u�W�F�N�g�v�[���ɒǉ�����֐������}�N��
// Ref���p�������N���X�ł̂ݎg�p�ł���
// class T : public Ref{
//  CREATE(T);
// }
// �̂悤�ɁACREATE�}�N���Ɏ��g�̃N���X����n�����ƂŁAT::Create���쐬�����
#define CREATE(C)								\
static C* Create(){								\
	C* c = new C;								\
	if(c != nullptr){							\
		ObjectPoolManager::GetInstance()->		\
					GetCurrentPool()->Add(c);	\
		return c;								\
	}											\
	return nullptr;								\
}

// �쐬�Ɏ��s����Ref���p�����邽�߂̃}�N��
// REF_CLASS(T){};
// �̗l�ɏ�����Ref���p�������N���XT���o����
// CREATE�}�N�������̃}�N����œ����ɒǉ������������_�L
#define REF_CLASS(CLASS) class CLASS : public Ref


// ����}�N��
// REF_CLASS_EX(T)
//  ...
// REF_CLASS_END
// �Ƃ����Ref���p�����AT::Create���ǉ����ꂽ�N���X�������
// �Ō��REF_CLASS_END�݂̂��Ƃ��Ȃ����ǂ��ɂ����������ACREATE�}�N���𓯎��ɒǉ�����ɂ͌��󂱂ꂪ�œK��
#define REF_CLASS_EX(CLASS) class CLASS : public Ref{	\
	CREATE(CLASS);		\

#define REF_CLASS_END };
 

#endif	// end of Macro