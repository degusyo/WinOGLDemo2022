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


// 交差判定
bool CShape::CrossCheckIn(CVertex* start_v, CVertex* end_v)
{
	// TODO: ここに実装コードを追加します.
	for (CVertex* v = vertex_head; v != NULL; v = v->GetNextVertex())
	{
		// 交差判定する点を設定
		CVertex* a_s = NULL;
		CVertex* a_e = NULL;
		CVertex* b_s = NULL;
		CVertex* b_e = NULL;
		
		if (v->GetNextVertex() != NULL)
		{
			a_s = v;
			a_e = v->GetNextVertex();
			b_s = start_v;
			b_e = end_v;
		}
		else if (close_flag)
		{
			a_s = v;
			a_e = vertex_head;
			b_s = start_v;
			b_e = end_v;
		}
		else continue;

		// ベクトルを求める
		CVertex a, b, a1, a2, b1, b2;
		a.SetXY(a_e->GetX() - a_s->GetX(), a_e->GetY() - a_s->GetY());
		b.SetXY(b_e->GetX() - b_s->GetX(), b_e->GetY() - b_s->GetY());
		a1.SetXY(b_s->GetX() - a_s->GetX(), b_s->GetY() - a_s->GetY());
		a2.SetXY(b_e->GetX() - a_s->GetX(), b_e->GetY() - a_s->GetY());
		b1.SetXY(a_s->GetX() - b_s->GetX(), a_s->GetY() - b_s->GetY());
		b2.SetXY(a_e->GetX() - b_s->GetX(), a_e->GetY() - b_s->GetY());

		 // 交差判定
		float ca1, ca2, cb1, cb2;

		ca1 = a.GetX() * a1.GetY() - a.GetY() * a1.GetX();
		ca2 = a.GetX() * a2.GetY() - a.GetY() * a2.GetX();
		cb1 = b.GetX() * b1.GetY() - b.GetY() * b1.GetX();
		cb2 = b.GetX() * b2.GetY() - b.GetY() * b2.GetX();

		if (ca1 * ca2 < 0 && cb1 * cb2 < 0)
		{
			return false;
		}
	}

	return true;
}


// 内包判定
bool CShape::Insection_Judge(float x, float y)
{
	// TODO: ここに実装コードを追加します.
	float n = 0.0f;
	for (CVertex* v_cell = vertex_head; v_cell != NULL; v_cell = v_cell->GetNextVertex())
	{
		CVertex a, b;

		if (v_cell->GetNextVertex() != NULL)
		{
			// ベクトルの算出
			a.SetXY(v_cell->GetX() - x, v_cell->GetY() - y);
			b.SetXY(v_cell->GetNextVertex()->GetX() - x, v_cell->GetNextVertex()->GetY() - y);
		}
		else
		{
			a.SetXY(v_cell->GetX() - x, v_cell->GetY() - y);
			b.SetXY(vertex_head->GetX() - x, vertex_head->GetY() - y);
		}

		// 外積・内積の計算
		float cross, dot;

		cross = a.GetX() * b.GetY() - a.GetY() * b.GetX();
		dot = a.GetX() * b.GetX() + a.GetY() * b.GetY();

		// 角度を計算
		n += (float)atan2(cross, dot);
	}

	if (abs(n) <= 0.001)	return false;
	return true;
}
