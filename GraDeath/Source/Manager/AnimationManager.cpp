#include "Manager/AnimationManager.h"
#include "Loader/PlayerLoader.h"
#include "Object/Player.h"

bool AnimationManager::Create(unsigned int playerNum, Player* _player){
	player = _player;

	PlayerLoader::LoadFile(playerNum, &animation);
	player->Init(animation.fileName, b2Vec2((150 + static_cast<float>(playerNum)* 300.f) / 32.0f, 200.0f/32.0f));//468/32.0f));

	ChangeAction(ACTION_IDLE, true);

	return true;
}


void AnimationManager::ChangeAction(PLAYER_ACTION _action, bool _loop){
	currentAction = _action;
	loop = _loop;
	currentCell = animation.cellDatas[currentAction].begin();
	AttachFixtureToPlayer();
}

CURRENT_ANIMATION_STATE AnimationManager::Update(){
	// アニメーションが有効で、現在の表示フレームがセル毎の設定フレームより大きくなったら
	// 次のセルに進もうとする
	if (isEnable && (*currentCell)->animFrame <= currentFrame++){
		auto nextCell = currentCell + 1;
		// 次のセルが無ければセルの頭に戻るか、終わったことを通知する
		if (nextCell == animation.cellDatas[currentAction].end()){
			if (loop){
				currentCell = animation.cellDatas[currentAction].begin();
				AttachFixtureToPlayer();
				currentFrame = 0;
			}
			else{
				return FINISHED;
			}
		}
		// 次のセルがあればそのセルを現在のセルとする
		else{
			++currentCell;
			if ((*currentCell)->se != nullptr){
				(*currentCell)->se->Stop();
				(*currentCell)->se->Play();
			}
			AttachFixtureToPlayer();
			currentFrame = 0;
		}
	}
	return PROCESSED;
}

void AnimationManager::GetDrawingRect(D2D1_RECT_F& rect){
	auto size = animation.cellSize;
	size_t pos = std::distance(animation.cellDatas[currentAction].begin(), currentCell);
	rect.left = size.x * pos;
	rect.top = size.y * (int)currentAction;
	rect.right = size.x;
	rect.bottom = size.y;
}

const D3DXVECTOR2& AnimationManager::GetCellSize(){
	return animation.cellSize;
}

void AnimationManager::AttachFixtureToPlayer(){
	player->AttachFixture((*currentCell)->shapes);
}