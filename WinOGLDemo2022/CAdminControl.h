#pragma once
#include "gl/GL.h" // 忘れない！！
#include "CVertex.h"
#include "CShape.h"
#include "math.h"

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
	// 内包判定
	bool Insection_Judge(float x, float y);
	void DrawAxis();
	// XYZ軸フラグ
	bool AxisFlag;
private:
	// 編集モードフラグ
	bool EditFlag;
public:
	// 編集フラグ切替
	void ChangeEditFlag();
	// 編集フラグ返却
	bool GetEditFlag();
private:
	// 選択された頂点
	CVertex* select_vertex;
	// 選択された線分の開始点
	CVertex* select_linestart;
	// 選択された線分の終了点
	CVertex* select_lineend;
	// 選択された図形
	CShape* select_shape;
	// 頂点の選択
	void SelectVertex(float Press_x, float Press_y);
	// 稜線の選択
	void SelectLine(float Press_x, float Press_y);
public:
	// 編集
	void Edit(float Press_x, float Press_y);
	// 選択・編集内容を描画
	void EditDraw();
	// 形状選択
	void SelectShape(float Press_x, float Press_y);
};

