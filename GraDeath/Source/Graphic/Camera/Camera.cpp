#include "Graphic/D3DGraphic.h"
#include "Graphic/Camera/Camera.h"

namespace Graphic{
	namespace Camera{
		class Pimpl;
	}

	class Camera::Pimpl{
	public:
		Pimpl();
		void Update();
		const D3DXMATRIX& GetView();
		const D3DXMATRIX& GetProjection();
		const D3DXMATRIX& GetViewport();
		const D3DXVECTOR3& GetPosition();
		const D3DXVECTOR3& GetLookVec();
		const D3DXVECTOR3& GetLookAt();

		void SetPosition(const D3DXVECTOR3& _pos);
		void SetDistance(float _distance);
		void SetLookAt(const D3DXVECTOR3& _at);
		void SetLookAt(const D3DXVECTOR3& _pos, const D3DXVECTOR3& _look, const D3DXVECTOR3& _up = D3DXVECTOR3(0, 1, 0));
		void SetPerspective(float fov, float aspect, float _near, float _far);
		void SetViewport(int width, int height);
		void Rotate(const D3DXVECTOR2& rot);

		D3DXMATRIX viewport;
		D3DXMATRIX view;
		D3DXMATRIX proj;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 lookat;				// ターゲット（見る対象）
		D3DXVECTOR3 upVector;
		D3DXVECTOR3 normalizeLookVec;	// ターゲットまでの正規化されたベクトル

		CAMERA_MODE mode;
		float distance;				// ターゲットからカメラまでの距離
		float fov;
		float aspect;
		float nearZ;
		float farZ;
		void(Camera::Pimpl::*Updates[2])();

	private:
		void UpdateFPS();
		void UpdateTPS();
	};


	Camera::Pimpl::Pimpl(){
		D3DXMatrixIdentity(&viewport);
		D3DXMatrixIdentity(&view);
		D3DXMatrixIdentity(&proj);

		mode = MODE_FPS;
		Updates[MODE_FPS] = &Camera::Pimpl::UpdateFPS;
		Updates[MODE_TPS] = &Camera::Pimpl::UpdateTPS;

		distance = 1;
	}

	void Camera::Pimpl::Update(){
		D3DXVECTOR3 d = lookat - pos;
		distance = D3DXVec3Length(&d);
		D3DXVec3Normalize(&normalizeLookVec, &d);

		D3DXVec3Scale(&lookat, &normalizeLookVec, distance);
		D3DXVec3Add(&lookat, &lookat, &pos);

		(this->*Updates[mode])();
	}

	void Camera::Pimpl::UpdateFPS(){
		D3DXMatrixLookAtLH(&view, &pos, &lookat, &upVector);
	}

	void Camera::Pimpl::UpdateTPS(){
		D3DXMatrixLookAtLH(&view, &lookat, &pos, &upVector);
	}

	void Camera::Pimpl::SetLookAt(const D3DXVECTOR3& _at){
		//mode == MODE_TPS ? lookat = _at : pos = _at;
		if (mode == MODE_FPS){
			lookat = _at;
		}
		else{
			pos = _at;
		}
	}

	void Camera::Pimpl::SetLookAt(const D3DXVECTOR3& _pos, const D3DXVECTOR3& _look, const D3DXVECTOR3& _up){
		if (mode == MODE_FPS){
			pos = _pos;
			lookat = _look;
		}
		else{
			pos == _look;
			lookat = _pos;
		}
		upVector = _up;
	}

	void Camera::Pimpl::SetPosition(const D3DXVECTOR3& _pos){
		//mode == MODE_FPS ? pos = _pos : lookat = _pos;
		if (mode == MODE_FPS){
			pos = _pos;
		}
		else{
			lookat = _pos;
		}
	}

	void Camera::Pimpl::SetDistance(float _distance){
		distance = _distance;
	}

	void Camera::Pimpl::Rotate(const D3DXVECTOR2& rot){
		D3DXQUATERNION qua;
		D3DXMATRIX tmp;
		D3DXQuaternionRotationAxis(&qua, &D3DXVECTOR3(-normalizeLookVec.z, 0, normalizeLookVec.x), rot.x);
		D3DXMatrixRotationQuaternion(&tmp, &qua);
		D3DXVec3TransformCoord(&normalizeLookVec, &normalizeLookVec, &tmp);
		D3DXMatrixRotationY(&tmp, rot.y);
		D3DXVec3TransformCoord(&normalizeLookVec, &normalizeLookVec, &tmp);
	}

	void Camera::Pimpl::SetPerspective(float _fov, float _aspect, float _near, float _far){
		fov = _fov;
		aspect = _aspect;
		nearZ = _near;
		farZ = _far;
		D3DXMatrixPerspectiveFovLH(&proj, fov, aspect, nearZ, farZ);
	}

	void Camera::Pimpl::SetViewport(int width, int height){
		viewport._11 = (float)width / 2;
		viewport._41 = (float)width / 2;
		viewport._22 = (float)-height / 2;
		viewport._42 = (float)height / 2;
		viewport._33 = 1.0f;
		viewport._44 = 1.0f;
		D3D::RS::SetViewport ( width, height );
	}

	namespace {
		Camera::Pimpl pimpl;
	}

	void Camera::Update(){
		pimpl.Update();
	}

	void Camera::SetLookAt(const D3DXVECTOR3& _at){
		pimpl.SetLookAt(_at);
	}

	void Camera::SetLookAt(const D3DXVECTOR3& _pos, const D3DXVECTOR3& _look, const D3DXVECTOR3& _up){
		pimpl.SetLookAt(_pos, _look, _up);
	}

	void Camera::SetPosition(const D3DXVECTOR3& _pos){
		pimpl.SetPosition(_pos);
	}

	void Camera::SetPerspective(float _fov, float aspect, float _near, float _far){
		pimpl.SetPerspective(_fov, aspect, _near, _far);
	}

	void Camera::SetViewport(int width, int height){
		pimpl.SetViewport(width, height);
	}

	void Camera::SetDistance(float _distance){
		pimpl.SetDistance(_distance);
	}

	void Camera::Rotate(const D3DXVECTOR2& rot){
		pimpl.Rotate(rot);
	}

	const D3DXMATRIX& Camera::GetProjection(){
		return  pimpl.proj;
	}

	const D3DXMATRIX& Camera::GetView(){
		return  pimpl.view;
	}

	const D3DXMATRIX& Camera::GetViewport(){
		return pimpl.viewport;
	}

	const D3DXVECTOR3& Camera::GetPosition(){
		return pimpl.pos;
	}

	const D3DXVECTOR3& Camera::GetLookVec(){
		return pimpl.normalizeLookVec;
	}

	const D3DXVECTOR3& Camera::GetLookAt(){
		return pimpl.lookat;
	}

};