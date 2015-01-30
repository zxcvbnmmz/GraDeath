// �C���N���[�h ***********************************************
#include "Utility/FPS.h"

// �R���X�g���N�^
FPS::FPS() :
timeStart(0), timeEnd(0), timeSum(0), Counter(0), lockFPS(60), aveFPS(60)
{
}

// �f�X�g���N�^
FPS::~FPS()
{
}

// �t���[���̃E�F�C�g
void FPS::WaitFrame()
{
	if (lockFPS <= Counter)
	{
		aveFPS = 1000.0f / (static_cast< float >(timeSum) / lockFPS);
		timeSum = 0;
		Counter = 0;
	}

	Counter++;

	timeEnd = timeGetTime();

	int waitTime = 1000 / static_cast< int >(lockFPS)-static_cast< int >(timeEnd - timeStart);

	bool waitFlg = (0 < waitTime);

	if (waitFlg) Sleep(waitTime);

	timeSum += timeGetTime() - timeStart;
	timeStart = timeGetTime();

}

// FPS�̐ݒ�
void FPS::SetFPS(float set)
{
	lockFPS = set;
	aveFPS = set;
}

// FPS�̎擾
float FPS::GetFPS()
{
	return aveFPS;
}