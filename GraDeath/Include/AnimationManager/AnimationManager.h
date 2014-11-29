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
		// 読み込みをここで
	}

	void ChangeAction(ACTION _action, bool _loop){
		currentAction = _action;
		loop = _loop;
		currentCell = animation.cellDatas[currentAction].begin();
	}

	CURRENT_STATE Update(){
		// アニメーションが有効で、現在の表示フレームがセル毎の設定フレームより大きくなったら
		// 次のセルに進もうとする
		if (isEnable && (*currentCell)->animFrame <= currentFrame++){
			auto nextCell = currentCell + 1;
			// 次のセルが無ければセルの頭に戻るか、終わったことを通知する
			if (nextCell == animation.cellDatas[currentAction].end()){
				if (loop){
					currentCell = animation.cellDatas[currentAction].begin();
				}
				else{
					return FINISHED;
				}
			}
			// 次のセルがあればそのセルを現在のセルとする
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