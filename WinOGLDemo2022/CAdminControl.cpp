#include "pch.h"
#include "CAdminControl.h"

CAdminControl::CAdminControl()
{
	shape_head = NULL;
}

CAdminControl::~CAdminControl()
{
	DeleteShape();
}


// 描画関数
void CAdminControl::Draw()
{
	// TODO: ここに実装コードを追加します.
	for (CShape* s = shape_head; s != NULL; s = s->GetNextShape())
	{
		for (CVertex* v = s->GetVertexHead(); v != NULL; v = v->GetNextVertex())
		{
			// 点の描画
			glColor3f(1.0, 1.0, 1.0);
			glPointSize(15);
			glBegin(GL_POINTS);
			glVertex2f(v->GetX(), v->GetY());
			glEnd();

			// 線の描画
			if (v->GetNextVertex() != NULL)
			{
				glColor3f(1.0, 1.0, 1.0);
				glLineWidth(5);
				glBegin(GL_LINES);
				glVertex2f(v->GetX(), v->GetY());
				glVertex2f(v->GetNextVertex()->GetX(), v->GetNextVertex()->GetY());
				glEnd();
			}
			else if (s->GetShapeCloseFlag())
			{
				glColor3f(1.0, 1.0, 1.0);
				glLineWidth(5);
				glBegin(GL_LINES);
				glVertex2f(v->GetX(), v->GetY());
				glVertex2f(s->GetVertexHead()->GetX(), s->GetVertexHead()->GetY());
				glEnd();
			}
			
		}
	}
	
}


// 左押し込み座標格納
void CAdminControl::SetLPress_XY(float x, float y)
{
	// TODO: ここに実装コードを追加します.
	LPress_x = x;
	LPress_y = y;
}


// 頂点追加
void CAdminControl::NewSetVertex(float new_x, float new_y)
{
	// TODO: ここに実装コードを追加します.
	// 作成中の形状がないか判定
	if (!Insection_Judge(new_x, new_y))
	{
		if (shape_head == NULL || shape_head->GetShapeCloseFlag())
		{
			CShape* new_shape = new CShape;

			// 一個目の形状か
			if (shape_head != NULL)
			{
				new_shape->SetNextShape(shape_head);
			}
			shape_head = new_shape;

			// 頂点追加
			shape_head->SetNewVertex(new_x, new_y);
		}
		else
		{
			// 形状を閉じるかの判定
			if (shape_head->GetVertexCount() > 2)
			{
				// 端点との距離計算
				float dis = 0.0f;
				CVertex* end_vertex = NULL;
				for (CVertex* cell = shape_head->GetVertexHead(); cell != NULL; cell = cell->GetNextVertex())
				{
					end_vertex = cell;
				}

				dis = pow(end_vertex->GetX() - new_x, 2) + pow(end_vertex->GetY() - new_y, 2);
				dis = sqrt(dis);

				if (dis < 0.2)
				{
					CVertex* end_v = NULL;
					for (CVertex* v = shape_head->GetVertexHead(); v != NULL; v = v->GetNextVertex())
					{
						end_v = v;
					}

					for (CShape* s_cell = shape_head; s_cell != NULL; s_cell = s_cell->GetNextShape())
					{
						if (shape_head != s_cell)
							if (shape_head->Insection_Judge(s_cell->GetVertexHead()->GetX(), s_cell->GetVertexHead()->GetY()))
							{
								return;
							}
					}
					if (CrossCheckOut(shape_head->GetVertexHead(), end_v))
					{
						shape_head->CloseShape();
						return;
					}
				}
			}

			CVertex v;
			v.SetXY(new_x, new_y);
			if (CrossCheckOut(&v, shape_head->GetVertexHead()))
			{
				shape_head->SetNewVertex(new_x, new_y);
			}
		}
	}
}


// Shapeのメモリ開放
void CAdminControl::DeleteShape()
{
	// TODO: ここに実装コードを追加します.
	while (shape_head != NULL)
	{
		CShape* del_s;
		del_s = shape_head;
		shape_head = shape_head->GetNextShape();

		delete del_s;
	}
}




// 他交差判定
bool CAdminControl::CrossCheckOut(CVertex* start_v, CVertex* end_v)
{
	// TODO: ここに実装コードを追加します.
	for (CShape* s = shape_head; s != NULL; s = s->GetNextShape())
	{
		if (!s->CrossCheckIn(start_v, end_v))	return false;
	}

	return true;
}


// 内包判定
bool CAdminControl::Insection_Judge(float x, float y)
{
	// TODO: ここに実装コードを追加します.
	for (CShape* s_cell = shape_head; s_cell != NULL; s_cell = s_cell->GetNextShape())
	{
		if (s_cell->GetShapeCloseFlag() && s_cell->Insection_Judge(x, y))	return true;
	}

	return false;
}
