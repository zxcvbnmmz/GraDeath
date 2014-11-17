#ifndef _OBJECT_PARAMETER_H_
#define _OBJECT_PARAMETER_H_

#include <vector>
#include <D3DX10math.h>
#include <memory>

enum COLLISION_MODEL
{
	CUBE = 0,
	SPHERE = 1,
};

enum Type
{
	ATTACK = 0,
	DAMEGE = 1,
	ATTACK_AND_DAMEGE = 2,
	SUPER_ARMOR = 4,
};

// 形データ
struct ShapeData
{
	short	collisionModel;	// 当たり判定の形(0=長方形:1=円)
	short	collisionType;	// 当たり判定の種類(0=攻め:1=受け:2=両方:3=無敵)
	short	strength;		// 強さ
	union {
		struct {
			int x[ 4 ];		// 0:左上 1:右上 2:右下 3:左下
			int y[ 4 ];
		}square;
		struct {
			int x;			// 中心
			int y;
			int rad;		// 半径
		}circle;
	}shape;
};


// アニメーションのループ
struct CellData
{
	short	animUse;		// セルを使用するかしないか
	short	animType;		// アニメーションタイプ(0=立ち:1=移動:2=ジャンプ:3=攻撃:4=空白)
	short	animFrame;		// 1コマに必要なフレーム数
	//short	effectCount;	// エフェクト名の文字数
	//char*	effectFile;		// エフェクト名
	//short	soundCount;		// サウンド名の文字数
	//char*	soundFile;		// サウンドファイル
	short	shapeCount;		// 形数

	std::vector< std::shared_ptr< ShapeData > > shapeData;	// 形データ
};


struct AnimationData
{
	// 今後HPなどのデータを格納する可能性あり(証言：正田)
	char* fileName;
	D3DXVECTOR2 cellSize;		// セルのサイズ
	int rectWCount;		// 分割数
	int rectHCount;		// 分割数
	std::vector< std::vector< std::shared_ptr< CellData > > > cellDatas;
};


#endif