#ifndef _REF_H__
#define _REF_H__

#include "ObjectPool.h"
#include "Utility/Macro.h"

class Ref{
protected:
	Ref();
	Ref* AddReleasedList();

public:
	virtual ~Ref(){}
	void Release();

	// �h���N���X��Create�}�N������������Ă��Ȃ��ꍇ�ARef::Create���Ă΂��
	// ���̊֐���deprecated�ɂ��g�p���֎~���Ă���̂ŁA�h���N���X�ł�Create�֐��̎��������v���Ă���
	__declspec(deprecated("Please use the function of a derived class"))CREATE(Ref);

private:
	unsigned int refCount;
};

#endif	// end of Ref