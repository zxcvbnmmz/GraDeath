#include "Scene/TitleScene.h"
#include "Model/CwnStaticMesh.h"
#include "Model/ModelStaticShader.h"
#include "Graphic/Camera/Camera.h"
#include "System/Window.h"

#include "Graphic/Rasterizer/Rasterizer.h"
#include "Graphic/BlendState/BlendState.h"
#include "Graphic/DepthStencil/DepthStencil.h"

#include "D2D/Sprite/Sprite.h"

Sprite sprite;

TitleScene::TitleScene(){

	int _w, _h;
	System::Window::GetWindowSize ( &_w, &_h );
	Graphic::Camera::SetViewport ( _w, _h );
	Graphic::Camera::SetPerspective ( ( float )D3DX_PI / 4.0f, (float)_w / (float)_h, 0.1f, 100.0f );
	Graphic::Camera::SetLookAt ( D3DXVECTOR3 (  0, 40 ,-60 ), D3DXVECTOR3 ( 0, 0, 0 ) );
	Graphic::Camera::Update ();

	testModel = std::shared_ptr< CwnStaticMesh > ( new CwnStaticMesh );
	testModel->LoadCwn ( "Magician.cwn", "Resource/Model/Character/Archer/" );
	modelStaticShader.Compile ();

	sprite.Create(L"Resource/Texture/Test.png");
}

SCENE_STATUS TitleScene::Execute(){

	Graphic::Camera::Update ();

	return STILL_PROCESSING;
}

void TitleScene::Draw(){
	Graphic::Rasterizer::CullNone();
	Graphic::BlendState::Lenear();
	Graphic::DepthStencil::DepthDefault();
	D3DXMATRIX world, matScale, matRot, matTrans;

	D3DXMatrixScaling ( &matScale, 1.0f, 1.0f, 1.0f );

	static float r = 0;
	r += 0.005f;
	D3DXMatrixRotationYawPitchRoll ( &matRot, r, 0, 0 );
	D3DXMatrixTranslation ( &matTrans, 0, 0, 0 );

	// ƒ[ƒ‹ƒhs—ñ‚ÉŠ|‚¯‡‚í‚¹
	world = matScale * matRot * matTrans;

	ModelStaticDatas msDatas;
	msDatas.data.light = D3DXVECTOR4(0.5, 0.5, 0.5, 1);
	msDatas.data.world = world;
	msDatas.data.wvp = world * Graphic::Camera::GetView() * Graphic::Camera::GetProjection();

	//testModel->Render ( &modelStaticShader, &msDatas );

	sprite.Draw();
}
