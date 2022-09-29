#pragma once
#include "gl/GL.h" // 忘れない！！
#include "CVertex.h"
#include "CShape.h"

class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();
	// 描画関数
	void Draw();
private:
	// 左押し込みx座標
	float LPress_x;
	// 左押し込みy座標
	float LPress_y;
	// Shapeリストの先頭
	CShape* shape_head;
public:
	// 左押し込み座標格納
	void SetLPress_XY(float x, float y);
	// 頂点追加
	void NewSetVertex(float new_x, float new_y);
	// Shapeのメモリ開放
	void DeleteShape();
	// 他交差判定
	bool CrossCheckOut(CVertex* start_v, CVertex* end_v);
};

