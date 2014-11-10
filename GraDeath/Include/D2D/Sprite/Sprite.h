//--------------------------------------------
// @filename	Sprite.h
// @outline		Direct2D用テクスチャクラス
//--------------------------------------------

//--------------------------------------------
// インクルードガード
//--------------------------------------------
#ifndef _SPRITE_H__
#define _SPRITE_H__

//--------------------------------------------
// インクルード
//--------------------------------------------
#include <D2D1.h>
#include <D3DX10.h>

//--------------------------------------------
// 列挙体
//--------------------------------------------

//--------------------------------------------
// @todo
//  Spriteを描画する際の反転フラグとして使用
// @contents
//  FLIP_NONE			反転なし（デフォルト）
//  FLIP_HORIZONTAL		左右反転
//  FLIP_VERTICAL		上下反転
//  FLIP_UPSIDE_DOWN	上下左右反転
//--------------------------------------------
enum REVERSE_FLAG{
	FLIP_NONE		=	0,
	FLIP_HORIZONTAL	=	1,
	FLIP_VERTICAL	=	2,
	FLIP_UPSIDE_DOWN =	FLIP_HORIZONTAL | FLIP_VERTICAL
};

enum DRAW_EFFECT{
	DRAW_NORMAL = 1,
	DRAW_RECT = 2,
	DRAW_AFFINE = 4
};

//--------------------------------------------
// クラス本体
//--------------------------------------------
class Sprite{
public:
	//--------------------------------------------
	// @name
	//  Sprite::Sprite()
	// @access modifier
	//  public
	// @todo
	//  コンストラクタ
	//--------------------------------------------
	Sprite();

	//--------------------------------------------
	// @name
	//  Sprite::Sprite()
	// @access modifier
	//  public
	// @todo
	//  デストラクタ
	//--------------------------------------------
	~Sprite();

	//--------------------------------------------
	// @name
	//  bool Sprite::Create(LPCWSTR fileName)
	// @access modifier
	//  public
	// @param
	//  LPCWSTR	fileName	テクスチャのファイルパス
	// @retval
	//  bool	テクスチャの生成に失敗したり、
	//			すでにテクスチャを保持していた場合はfalseを返す
	// @todo
	//  テクスチャを生成し、保持する
	//--------------------------------------------
	bool Create(LPCWSTR fileName);

	//--------------------------------------------
	// @name
	//  Sprite::Draw(DRAW_EFFECT effect)
	// @access modifier
	//  public
	// @todo
	//  テクスチャの描画
	//--------------------------------------------
	void Draw(DRAW_EFFECT effect = DRAW_NORMAL);

	//--------------------------------------------
	// @name
	//  Sprite::DrawRect()
	// @access modifier
	//  public
	// @todo
	//  テクスチャ（矩形）の描画
	//--------------------------------------------
	void DrawRect();

	//--------------------------------------------
	// @name
	//  Sprite::DrawAffine()
	// @access modifier
	//  public
	// @todo
	//  テクスチャ（矩形、アフィン変換）の描画
	//--------------------------------------------
	void DrawAffine();

	//--------------------------------------------
	// @name
	//  const D2D1_RECT_F* Sprite::GetSize()
	// @access modifier
	//  public
	// @retval
	//  const D2D1_RECT_F*	テクスチャのサイズ
	// @todo
	//  テクスチャのスケーリングされていない場合のサイズを返す
	//--------------------------------------------
	const D2D1_RECT_F* GetSize();	

	//--------------------------------------------
	// @name
	//  D3DXVECTOR2 Sprite::GetPosition()
	// @access modifier
	//  public
	// @retval
	//  D3DXVECTOR2		テクスチャの座標
	// @todo
	//  テクスチャの座標を返す
	//--------------------------------------------
	D3DXVECTOR2 GetPosition();

	//--------------------------------------------
	// @name
	//  D3DXVECTOR2 Sprite::GetDefaultSize()
	// @access modifier
	//  public
	// @retval
	//  D3DXVECTOR2		テクスチャのサイズ
	// @todo
	//  読み込んだテクスチャの元のサイズを返す
	//--------------------------------------------
	D3DXVECTOR2 GetDefaultSize();

	//--------------------------------------------
	// @name
	// 　void Sprite::SetAlpha()
	// @access modifier
	//  public
	// @todo
	//  アルファ値を設定する
	// @memo
	//  アルファ値は0～1の間
	//--------------------------------------------
	void SetAlpha(float _alpha);
	void SetDefaultSize();

	void SetPosition(float x, float y);
	void SetPosition(const D3DXVECTOR2& vec);
	void SetPositionX(float x);
	void SetPositionY(float y);
	
	void SetSize(float x, float y);
	void SetSize(const D3DXVECTOR2& vec);
	void SetSize(const D2D1_SIZE_F& size);
	void SetSizeX(float x);
	void SetSizeY(float y);

	void SetScale(float x, float y);
	void SetWeight(int x, int y);

	void SetRotation(float _degree);
	void SetSkew(float xDeg, float yDeg);

	void SetTrimming(int x, int y, int wSize, int hSize);
	void SetTrimming(const D3DXVECTOR2& pos, const D3DXVECTOR2& size);
	void SetTrimming(int x, int y, const D3DXVECTOR2& size);
	void SetTrimming(const D3DXVECTOR2& pos, int wSize, int hSize);

	void SetReverseFlag(REVERSE_FLAG flag);
	bool IsValid();

private:
	Sprite(const Sprite&);
	Sprite& operator=(const Sprite&);

	ID2D1Bitmap* bitmap;
	D2D1_SIZE_F size;
	D2D1_RECT_F trim;	// 切り取りサイズ保持用
	D2D1_POINT_2F pos;
	D2D1_POINT_2F weight;
	D2D1_SIZE_F scale;
	D2D1_POINT_2F skew;
	REVERSE_FLAG reverseFlag;
	float degree = 0;
	float alpha = 0;
};

#endif	// end of Sprite
