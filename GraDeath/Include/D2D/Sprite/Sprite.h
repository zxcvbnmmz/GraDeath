//--------------------------------------------
// @filename	Sprite.h
// @outline		Direct2D�p�e�N�X�`���N���X
//--------------------------------------------

//--------------------------------------------
// �C���N���[�h�K�[�h
//--------------------------------------------
#ifndef _SPRITE_H__
#define _SPRITE_H__

//--------------------------------------------
// �C���N���[�h
//--------------------------------------------
#include <D2D1.h>
#include <D3DX10.h>

//--------------------------------------------
// �񋓑�
//--------------------------------------------

//--------------------------------------------
// @todo
//  Sprite��`�悷��ۂ̔��]�t���O�Ƃ��Ďg�p
// @contents
//  FLIP_NONE			���]�Ȃ��i�f�t�H���g�j
//  FLIP_HORIZONTAL		���E���]
//  FLIP_VERTICAL		�㉺���]
//  FLIP_UPSIDE_DOWN	�㉺���E���]
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
// �N���X�{��
//--------------------------------------------
class Sprite{
public:
	//--------------------------------------------
	// @name
	//  Sprite::Sprite()
	// @access modifier
	//  public
	// @todo
	//  �R���X�g���N�^
	//--------------------------------------------
	Sprite();

	//--------------------------------------------
	// @name
	//  Sprite::Sprite()
	// @access modifier
	//  public
	// @todo
	//  �f�X�g���N�^
	//--------------------------------------------
	~Sprite();

	//--------------------------------------------
	// @name
	//  bool Sprite::Create(LPCWSTR fileName)
	// @access modifier
	//  public
	// @param
	//  LPCWSTR	fileName	�e�N�X�`���̃t�@�C���p�X
	// @retval
	//  bool	�e�N�X�`���̐����Ɏ��s������A
	//			���łɃe�N�X�`����ێ����Ă����ꍇ��false��Ԃ�
	// @todo
	//  �e�N�X�`���𐶐����A�ێ�����
	//--------------------------------------------
	bool Create(LPCWSTR fileName);

	//--------------------------------------------
	// @name
	//  Sprite::Draw(DRAW_EFFECT effect)
	// @access modifier
	//  public
	// @todo
	//  �e�N�X�`���̕`��
	//--------------------------------------------
	void Draw(DRAW_EFFECT effect = DRAW_NORMAL);

	//--------------------------------------------
	// @name
	//  Sprite::DrawRect()
	// @access modifier
	//  public
	// @todo
	//  �e�N�X�`���i��`�j�̕`��
	//--------------------------------------------
	void DrawRect();

	//--------------------------------------------
	// @name
	//  Sprite::DrawAffine()
	// @access modifier
	//  public
	// @todo
	//  �e�N�X�`���i��`�A�A�t�B���ϊ��j�̕`��
	//--------------------------------------------
	void DrawAffine();

	//--------------------------------------------
	// @name
	//  const D2D1_RECT_F* Sprite::GetSize()
	// @access modifier
	//  public
	// @retval
	//  const D2D1_RECT_F*	�e�N�X�`���̃T�C�Y
	// @todo
	//  �e�N�X�`���̃X�P�[�����O����Ă��Ȃ��ꍇ�̃T�C�Y��Ԃ�
	//--------------------------------------------
	const D2D1_RECT_F* GetSize();	

	//--------------------------------------------
	// @name
	//  D3DXVECTOR2 Sprite::GetPosition()
	// @access modifier
	//  public
	// @retval
	//  D3DXVECTOR2		�e�N�X�`���̍��W
	// @todo
	//  �e�N�X�`���̍��W��Ԃ�
	//--------------------------------------------
	D3DXVECTOR2 GetPosition();

	//--------------------------------------------
	// @name
	//  D3DXVECTOR2 Sprite::GetDefaultSize()
	// @access modifier
	//  public
	// @retval
	//  D3DXVECTOR2		�e�N�X�`���̃T�C�Y
	// @todo
	//  �ǂݍ��񂾃e�N�X�`���̌��̃T�C�Y��Ԃ�
	//--------------------------------------------
	D3DXVECTOR2 GetDefaultSize();

	//--------------------------------------------
	// @name
	// �@void Sprite::SetAlpha()
	// @access modifier
	//  public
	// @todo
	//  �A���t�@�l��ݒ肷��
	// @memo
	//  �A���t�@�l��0�`1�̊�
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
	D2D1_RECT_F trim;	// �؂���T�C�Y�ێ��p
	D2D1_POINT_2F pos;
	D2D1_POINT_2F weight;
	D2D1_SIZE_F scale;
	D2D1_POINT_2F skew;
	REVERSE_FLAG reverseFlag;
	float degree = 0;
	float alpha = 0;
};

#endif	// end of Sprite
