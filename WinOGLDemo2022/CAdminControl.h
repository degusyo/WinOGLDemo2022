#pragma once
#include "gl/GL.h" // YêÈ¢II
#include "CVertex.h"
#include "CShape.h"

class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();
	// `æÖ
	void Draw();
private:
	// ¶µÝxÀW
	float LPress_x;
	// ¶µÝyÀW
	float LPress_y;
	// ShapeXgÌæª
	CShape* shape_head;
public:
	// ¶µÝÀWi[
	void SetLPress_XY(float x, float y);
	// ¸_ÇÁ
	void NewSetVertex(float new_x, float new_y);
	// ShapeÌJú
	void DeleteShape();
	// ¼ð·»è
	bool CrossCheckOut(CVertex* start_v, CVertex* end_v);
	// àï»è
	bool Insection_Judge(float x, float y);
};

