#include "pch.h"
#include "CShape.h"

CShape::CShape()
{
	vertex_cnt = 0;
	vertex_head = NULL;
	close_flag = false;
}

CShape::~CShape()
{
	DeleteVertex();
}


// 新しい点の設定
void CShape::SetNewVertex(float new_x, float new_y)
{
	// TODO: ここに実装コードを追加します.

	//新しい頂点生成
	CVertex* new_vertex = new CVertex;
	vertex_cnt++;

	// 座標格納
	new_vertex->SetXY(new_x, new_y);

	// リスト連結修正
	if (vertex_cnt > 1)
	{
		new_vertex->SetNextVertex(vertex_head);
	}
	vertex_head = new_vertex;
}


// 頂点リストの端点を返す
CVertex* CShape::GetVertexHead()
{
	// TODO: ここに実装コードを追加します.
	return vertex_head;
}


// 頂点数を返却
int CShape::GetVertexCount()
{
	// TODO: ここに実装コードを追加します.
	return vertex_cnt;
}


// 形状の閉じたかの判定返却
bool CShape::GetShapeCloseFlag()
{
	// TODO: ここに実装コードを追加します.
	return close_flag;
}


// 形状を閉じる
void CShape::CloseShape()
{
	// TODO: ここに実装コードを追加します.
	close_flag = true;
}


// next_shapeに次のShape先を格納
void CShape::SetNextShape(CShape* next_s)
{
	// TODO: ここに実装コードを追加します.
	next_shape = next_s;
}


// 次のShapeを返却
CShape* CShape::GetNextShape()
{
	// TODO: ここに実装コードを追加します.
	return next_shape;
}


// vertexのメモリ開放
void CShape::DeleteVertex()
{
	// TODO: ここに実装コードを追加します.
	while (vertex_head != NULL)
	{
		CVertex* del_v;
		del_v = vertex_head;
		vertex_head = vertex_head->GetNextVertex();

		delete del_v;
	}
}
