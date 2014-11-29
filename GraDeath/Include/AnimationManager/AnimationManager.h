#ifndef _ANIMATION_MANAGER_H__
#define _ANIMATION_MANAGER_H__

#include "Object/ObjectParameter.h"

enum ACTION{
	ACTION_IDLE,
	ACTION_WALK,
	ACTION_RUN,
	ACTION_ATTACK,
};

enum CURRENT_STATE{
	PROCESSED,
	FINISHED,
};

class AnimationManager{
public:
	AnimationManager(){}

	bool Create(const char* fileName){
		// �ǂݍ��݂�������
	}

	void ChangeAction(ACTION _action, bool _loop){
		currentAction = _action;
		loop = _loop;
		currentCell = animation.cellDatas[currentAction].begin();
	}

	CURRENT_STATE Update(){
		// �A�j���[�V�������L���ŁA���݂̕\���t���[�����Z�����̐ݒ�t���[�����傫���Ȃ�����
		// ���̃Z���ɐi�����Ƃ���
		if (isEnable && (*currentCell)->animFrame <= currentFrame++){
			auto nextCell = currentCell + 1;
			// ���̃Z����������΃Z���̓��ɖ߂邩�A�I��������Ƃ�ʒm����
			if (nextCell == animation.cellDatas[currentAction].end()){
				if (loop){
					currentCell = animation.cellDatas[currentAction].begin();
				}
				else{
					return FINISHED;
				}
			}
			// ���̃Z��������΂��̃Z�������݂̃Z���Ƃ���
			else{
				++currentCell;
				currentFrame = 0;
			}
		}
		return PROCESSED;
	}

	void GetDrawRect(D2D1_RECT_F& rect){
		auto size = animation.cellSize;
		size_t pos = std::distance(animation.cellDatas[currentAction].begin(), currentCell);
		rect.left = size.x * pos;
		rect.top = size.y * pos;
		rect.right = size.x;
		rect.bottom = size.y;
	}

	void Enable(bool flag){
		isEnable = flag;
	}

private:
	std::vector<std::shared_ptr<CellData>>::iterator currentCell;
	ACTION currentAction;
	unsigned int currentFrame;
	AnimationData animation;
	bool isEnable;
	bool loop;
};

#endif	// end of AnimationManager