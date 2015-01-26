#ifndef _CAPTURE_CAMERA_H__
#define _CAPTURE_CAMERA_H__

#include "D2D/Text/TextObject.h"

class CaptureCamera{
public:
	CaptureCamera();
	~CaptureCamera(){}

	void Update();
	void DrawDetail();

private:
	void RotateDegree();
	void MoveVertical();
	void CloseDistance();
	void Reset();

	float rotate;
	float height;
	float lookHeight;
	float distance;
	float x, z;
	int captureInterval;

	D2D::TextObject textObject;

};

#endif	// end of CaptureCamera