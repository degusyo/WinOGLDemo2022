#pragma once
#include "gl/GL.h" // YêÈ¢II
#include "CVertex.h"

class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();
	// `æÖ
	void Draw();
private:
	// ¶µİxÀW
	float LPress_x;
	// ¶µİyÀW
	float LPress_y;
public:
	// ¶µİÀWi[
	void SetLPress_XY(float x, float y);
};

