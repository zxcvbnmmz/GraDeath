#include "Manager/AnimationManager.h"
#include "Loader/PlayerLoader.h"

bool AnimationManager::Create(unsigned int playerNum){
	PlayerLoader::LoadFile(playerNum, &animation);
	

	return true;
}

void AnimationManager::ChangeAction(PLAYER_ACTION _action, bool _loop){
	currentAction = _action;
	loop = _loop;
	currentCell = animation.cellDatas[currentAction].begin();
}

CURRENT_STATE AnimationManager::Update(){
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

void AnimationManager::GetDrawingRect(D2D1_RECT_F& rect){
	auto size = animation.cellSize;
	size_t pos = std::distance(animation.cellDatas[currentAction].begin(), currentCell);
	rect.left = size.x * pos;
	rect.top = size.y * pos;
	rect.right = size.x;
	rect.bottom = size.y;
}