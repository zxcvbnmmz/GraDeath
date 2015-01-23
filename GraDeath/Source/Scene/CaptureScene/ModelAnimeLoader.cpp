// ************************************************************
// fliename	ModelAnimeLoader.cpp
// brief	���f�����[�_�[
// name		����@�T
// memo
// 2014.01.21
// ************************************************************


// �C���N���[�h ***********************************************
#include "Scene/CaptureScene/ModelAnimeLoader.h"
#include "Graphic/D2DGraphic.h"
#include "Graphic/D3DGraphic.h"
#include <Model/CwnSkinMesh.h>
#include <Model/CwnStaticMesh.h>
#include <Model/BoneAnimeData.h>
#include <Model/ModelSkinShader.h>
#include <Model/ModelStaticShader.h>
#include "Scene/CaptureScene/MathDef.h"
#include "Scene/CaptureScene/FileLoader.h"
#include "Scene/CaptureScene/ConvertChar.h"
#include "Scene/CaptureScene/KeyboardOperation.h"
#include <string.h>
#include "Graphic/Camera/Camera.h"
#include "D2D/Brush/SolidBrush.h"

static const D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
static const D3DXVECTOR3 rotation = D3DXVECTOR3(0, 0, 0);
static const D3DXVECTOR3 scale = D3DXVECTOR3(1, 1, 1);

// �R���X�g���N�^
ModelAnimeLoader::ModelAnimeLoader() : animes(0), drawFlg(false), drawAnimeFlg(false)
{
	loader = new FileLoader;
	keyOpe = new KeyboardOperation;
	mesh = 0;
	keyOpe->StateReset();
	// �Ǎ��p�֐��|�C���^�֊֐�������
	LoadFunc[0] = &ModelAnimeLoader::ModelLoader;
	LoadFunc[1] = &ModelAnimeLoader::AnimeLoader;
	// �`��p�X�V�|�C���^
	DrawFunc[0] = &ModelAnimeLoader::DrawModelName;
	DrawFunc[1] = &ModelAnimeLoader::DrawAnimeName;

	modelNum = animeNum = 0;

	skinShader = new ModelSkinShader;
	skinShader->Compile();
	staticShader = new ModelStaticShader;
	staticShader->Compile();

	modelFlg = animeFlg = false;
	textObject.format = ::D2D::TextFormat::Create(L"���I���I", 20.0f);
	textObject.brush = SolidBrush::Create(1,1,1,1);
}

// �f�X�g���N�^
ModelAnimeLoader::~ModelAnimeLoader()
{
	if (animes != NULL)
		animes->Release();
	SafeDelete(animes);
	SafeDelete(loader);
	SafeDelete(keyOpe);
	SafeDelete(mesh);
	SafeDelete(skinShader);
	SafeDelete(staticShader);
}

// �Ǎ�
void ModelAnimeLoader::Load(int num)
{
	(this->*LoadFunc[num])();
}

// �X�V
int ModelAnimeLoader::Update()
{
	keyOpe->Update();
	if (modelFlg)
	{
		SelectModel();
		return MODEL_END;
	}
	if (animeFlg)
	{
		SelectAnime();
		return ANIME_END;
	}
	return LOOP;
}

// �`��
void ModelAnimeLoader::DrawModel()
{
	if (mesh == NULL)
		return;

	D3DXMATRIX world;
	MathDef::CalculationWorld(&world, position, rotation, scale);

	if (drawFlg)
	{
		ModelStaticDatas mcb;
		mcb.data.world = world;
		mcb.data.wvp = world * Camera::GetView() * Camera::GetProjection();
		mcb.data.light = D3DXVECTOR4(0, 0, 1, 1);

		static_cast<CwnStaticMesh*>(mesh)->Render(staticShader, &mcb);
		//D3DGraphics::SetShader(staticShader);
		//D3D::Graphics::DrawCwnStaticMesh(static_cast< CwnStaticMesh* >(mesh), &mcb);
	}
	if (drawAnimeFlg)
	{
		ModelSkinDatas mscb;
		mscb.data.world = world;
		mscb.data.wvp = world * Camera::GetView() * Camera::GetProjection();

		CwnSkinMesh* temp = static_cast< CwnSkinMesh* >(mesh);
		temp->Render(skinShader, &mscb);
		//D3DGraphics::SetShader(skinShader);
		//D3DGraphics::DrawCwnSkinMesh(temp, &mscb);
		temp->AddAnimeCount(1);
	}
}

void ModelAnimeLoader::DrawModelText(int num)
{
	(this->*DrawFunc[num])();
}

// ���
void ModelAnimeLoader::Release()
{
}

// ���f�����[�_�[
void ModelAnimeLoader::ModelLoader()
{
	keyOpe->StateReset();
	if (!fileModelList.empty())
		fileModelList.clear();

	modelFlg = true;

	loader->ModelLoad();
	std::vector< std::string > tempList = loader->GetModelList();
	DWORD size = tempList.size();

	for (DWORD i = 0; i < size; i++)
	{
		std::string tempStr = tempList[i];
		int size = tempStr.size();
		int npos = tempStr.rfind('.', size);
		char temp[5];
		// �g���q�̊m�F
		temp[4] = '\0';
		for (int j = 0; j < 4; j++)
		{
			temp[j] = tempStr[npos + j];
		}
		// �g���q�����v�����������Ǎ�
		if (strcmp(temp, ".cwn") == 0 || strcmp(temp, ".CWN") == 0)
		{
			fileModelList.push_back(tempList[i]);
		}
	}
	tempList.clear();
	keyOpe->SetUpDownMax(fileModelList.size());
}

void ModelAnimeLoader::AnimeLoader()
{
	keyOpe->StateReset();
	if (!fileAnimeList.empty())
		fileAnimeList.clear();

	animeFlg = true;

	loader->AnimeLoad();
	std::vector< std::string > tempList = loader->GetAnimeList();
	DWORD size = tempList.size();

	for (DWORD i = 0; i < size; i++)
	{
		std::string tempStr = tempList[i];
		int size = tempStr.size();
		int npos = tempStr.rfind('.', size);
		char temp[5];
		// �g���q�̊m�F
		temp[4] = '\0';
		for (int j = 0; j < 4; j++)
		{
			temp[j] = tempStr[npos + j];
		}
		// �g���q�����v�����������Ǎ�
		if (strcmp(temp, ".sia") == 0 || strcmp(temp, ".SIA") == 0)
		{
			fileAnimeList.push_back(tempList[i]);
		}
	}
	tempList.clear();
	keyOpe->SetUpDownMax(fileAnimeList.size());
}

// ���f���̑I��
void ModelAnimeLoader::SelectModel()
{
	modelNum = keyOpe->GetUpDown();

	if (keyOpe->GetKeyState(KC_ENTER, INPUT_PUSH))
	{
		if (MessageBox(
			NULL,
			L"�I���������f����ǂݍ��݂܂��B",
			L"���f���̓Ǎ�", MB_YESNO) == IDNO)
		{
			return;
		}
		else
		{
			if (mesh != NULL)
				SafeDelete(mesh);

			mesh = new CwnSkinMesh;
			char* name = const_cast< char* >(fileModelList[modelNum].c_str());
			mesh->LoadCwn(name, "Model\\");
			modelFlg = false;
		}
	}
}

void ModelAnimeLoader::SelectAnime()
{
	animeNum = keyOpe->GetUpDown();
	if (keyOpe->GetKeyState(KC_ENTER, INPUT_PUSH))
	{
		if (MessageBox(
			NULL,
			L"�I���������f����ǂݍ��݂܂��B",
			L"���f���̓Ǎ�", MB_YESNO) == IDNO)
		{
			return;
		}
		else
		{
			if (animes != NULL)
			{
				if (MessageBox(
					NULL,
					L"���݂̃A�j���[�V�����������܂���낵���ł����H",
					L"���f���̓Ǎ�", MB_YESNO) == IDNO)
				{
					return;
				}
				else
				{
					animes->Release();
					SafeDelete(animes);
					drawFlg = true;
					drawAnimeFlg = false;
				}
			}
			animes = new BoneAnimeData;
			std::string temp = "Anime\\";
			temp += fileAnimeList[animeNum].c_str();
			char* name = const_cast< char* >(temp.c_str());
			animes->LoadAnime(name);
			animeFlg = false;
		}
	}
}

// ���f���l�[���̕`��
void ModelAnimeLoader::DrawModelName()
{
	DWORD size = fileModelList.size();
	char	temp[260] = { 0 };
	wchar_t file[260] = { 0 };
	for (DWORD i = 0; i < size; i++)
	{
		std::string tempStr = fileModelList[i];
		DWORD textSize = tempStr.size();
		for (DWORD j = 0; j < textSize; j++)
		{
			temp[j] = tempStr[j];
		}
		temp[textSize] = '\0';
		strcpy_s(temp, temp);
		ConvertWChar(temp, sizeof(file) / sizeof(file[0]), file);
		textObject.DrawString(180, 40 + 20 * (float)i, file);
	}
	textObject.DrawString(160, 40 + 20 * (float)modelNum, L"��");
}

void ModelAnimeLoader::DrawAnimeName()
{
	DWORD size = fileAnimeList.size();
	char	temp[260] = { 0 };
	wchar_t	file[260] = { 0 };
	for (DWORD i = 0; i < size; i++)
	{
		std::string tempStr = fileAnimeList[i];
		DWORD textSize = tempStr.size();
		for (DWORD j = 0; j < textSize; j++)
		{
			temp[j] = tempStr[j];
		}
		temp[textSize] = '\0';
		strcpy_s(temp, temp);
		ConvertWChar(temp, sizeof(file) / sizeof(file[0]), file);
		textObject.DrawString(180, 60 + 20 * (float)i, file);
	}
	textObject.DrawString(160, 60 + 20 * (float)animeNum, L"��");
}

void ModelAnimeLoader::SetModelDraw(bool model)
{
	if (drawAnimeFlg)
	{
		if (MessageBox(
			NULL,
			L"�A�j���[�V�������A�^�b�`����Ă��܂��B\n�`�悷��ꍇ�̓A�^�b�`����������܂��B\n��낵���ł����H",
			L"���f���̕`��", MB_YESNO) == IDNO)
		{
			return;
		}
		else
		{
			drawFlg = model;
			drawAnimeFlg = false;
		}
	}
	else
	{
		drawFlg = model;
	}
}

void ModelAnimeLoader::SetAnimeAttachi(bool anime)
{
	if (mesh == NULL || animes == NULL)
	{
		if (MessageBox(
			NULL,
			L"���f���A�܂��̓A�j���[�V�����������ׁA\n�A�^�b�`�ł��܂���B",
			L"�A�j���̃A�^�b�`", MB_OK))
		{
			return;
		}
	}

	if (drawAnimeFlg)
	{
		if (MessageBox(
			NULL,
			L"�A�j�����Z�b�g����Ă��܂��B\n�ʂ̃A�j�����A�^�b�`����ꍇ�͍ēx�A�j����ǂݍ���ł��������B",
			L"�A�j���̃A�^�b�`", MB_OK))
		{
			return;
		}
	}

	if (drawFlg)
	{
		if (MessageBox(
			NULL,
			L"���݂̃��f���ɃA�j�����A�^�b�`���܂��B\n��낵���ł����H",
			L"�A�j���̃A�^�b�`", MB_YESNO) == IDNO)
		{
			return;
		}
		else
		{
			drawFlg = false;
			drawAnimeFlg = anime;
			CwnSkinMesh* temp = static_cast< CwnSkinMesh* >(mesh);
			temp->SetAnimeData(animes->GetAnimeData(0));
			return;
		}
	}
	else
	{
		if (MessageBox(
			NULL,
			L"���f�����`�悳��Ă������ׁA�A�^�b�`�ł��܂���B",
			L"�A�j���̃A�^�b�`", MB_OK))
		{
			return;
		}
	}
}

void ModelAnimeLoader::ResetAnimateTime(){
	CwnSkinMesh* temp = static_cast< CwnSkinMesh* >(mesh);
	temp->SetAnimeCount(0);
}

bool ModelAnimeLoader::IsAnimationEnd(){
	CwnSkinMesh* temp = static_cast< CwnSkinMesh* >(mesh);
	return temp->GetAnimeEnd();
}