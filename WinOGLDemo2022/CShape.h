#pragma once
#include "CVertex.h"
#include "math.h"

class CShape
{
public:
	CShape();
	~CShape();
	// 新しい点の設定
	void SetNewVertex(float new_x, float new_y);
private:
	// vertexリストの最端を指すポインタ
	CVertex* vertex_head;
	// 頂点数
	int vertex_cnt;
	// 形状が閉じているかの判定
	bool close_flag;
public:
	// 頂点リストの端点を返す
	CVertex* GetVertexHead();
	// 頂点数を返却
	int GetVertexCount();
	// 形状の閉じたかの判定返却
	bool GetShapeCloseFlag();
	// 形状を閉じる
	void CloseShape();
private:
	// 次のShapeポインタ
	CShape* next_shape;
public:
	// next_shapeに次のShape先を格納
	void SetNextShape(CShape* next_s);
	// 次のShapeを返却
	CShape* GetNextShape();
	// vertexのメモリ開放
	void DeleteVertex();
};

