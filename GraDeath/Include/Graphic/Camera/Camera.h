#ifndef _CAMERA_H__
#define _CAMERA_H__

#include <D3DX10math.h>

enum CAMERA_MODE{ MODE_FPS, MODE_TPS };

namespace Graphic{
	namespace Camera{
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
		void ChangeBase();

		void Update();
	};
};



#endif	// end of Camera