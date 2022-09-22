#pragma once
#include "gl/GL.h" // –Y‚ê‚È‚¢II
#include "CVertex.h"

class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();
	// •`‰æŠÖ”
	void Draw();
private:
	// ¶‰Ÿ‚µ‚İxÀ•W
	float LPress_x;
	// ¶‰Ÿ‚µ‚İyÀ•W
	float LPress_y;
public:
	// ¶‰Ÿ‚µ‚İÀ•WŠi”[
	void SetLPress_XY(float x, float y);
};

