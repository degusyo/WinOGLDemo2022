#include "pch.h"
#include "CAdminControl.h"

CAdminControl::CAdminControl()
{
	shape_head = NULL;
	AxisFlag = false;
	EditFlag = false;
	select_vertex = NULL;
	select_linestart = NULL;
	select_lineend = NULL;
	select_shape = NULL;
}

CAdminControl::~CAdminControl()
{
	DeleteShape();
}


// 描画関数
void CAdminControl::Draw()
{
	if (AxisFlag) {
		DrawAxis();
	}

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

// 選択・編集内容を描画
void CAdminControl::EditDraw()
{
	// TODO: ここに実装コードを追加します.
	if (select_vertex != NULL)
	{
		// 点の描画
		glColor3f(0.0, 1.0, 1.0);
		glPointSize(15);
		glBegin(GL_POINTS);
		glVertex2f(select_vertex->GetX(), select_vertex->GetY());
		glEnd();
	}
	if (select_linestart != NULL)
	{
		glColor3f(0.0, 1.0, 1.0);
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex2f(select_linestart->GetX(), select_linestart->GetY());
		glVertex2f(select_lineend->GetX(), select_lineend->GetY());
		glEnd();
	}
	if (select_shape != NULL)
	{
		for (CVertex* v_cell = select_shape->GetVertexHead(); v_cell != NULL; v_cell = v_cell->GetNextVertex())
		{
			glColor3f(0.0, 1.0, 1.0);
			glPointSize(15);
			glBegin(GL_POINTS);
			glVertex2f(v_cell->GetX(), v_cell->GetY());
			glEnd();

			if (v_cell->GetNextVertex() != NULL)
			{
				glColor3f(0.0, 1.0, 1.0);
				glLineWidth(5);
				glBegin(GL_LINES);
				glVertex2f(v_cell->GetX(), v_cell->GetY());
				glVertex2f(v_cell->GetNextVertex()->GetX(), v_cell->GetNextVertex()->GetY());
				glEnd();
			}
			else
			{
				glColor3f(0.0, 1.0, 1.0);
				glLineWidth(5);
				glBegin(GL_LINES);
				glVertex2f(v_cell->GetX(), v_cell->GetY());
				glVertex2f(select_shape->GetVertexHead()->GetX(), select_shape->GetVertexHead()->GetY());
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

				if (dis < 0.1)
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


void CAdminControl::DrawAxis()
{
	// TODO: ここに実装コードを追加します.
	glBegin(GL_LINES);
	// x軸
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	// y軸
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	// z軸
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
}


// 編集フラグ切替
void CAdminControl::ChangeEditFlag()
{
	// TODO: ここに実装コードを追加します.
	if (EditFlag)
	{
		EditFlag = false;
	}
	else
	{
		EditFlag = true;
	}
}


// 編集フラグ返却
bool CAdminControl::GetEditFlag()
{
	// TODO: ここに実装コードを追加します.
	return EditFlag;
}


// 編集
void CAdminControl::Edit(float Press_x, float Press_y)
{
	// TODO: ここに実装コードを追加します.
	
	// 点の選択
	SelectVertex(Press_x, Press_y);
	

	// 線の選択
	if (select_vertex == NULL) 
	{
		SelectLine(Press_x, Press_y);
	}

	// 形状の選択
	if (select_linestart == NULL)
	{
		SelectShape(Press_x, Press_y);
	}

}

// 頂点の選択
void CAdminControl::SelectVertex(float Press_x, float Press_y)
{
	// TODO: ここに実装コードを追加します.
	select_vertex = NULL;
	for (CShape* s_cell = shape_head; s_cell != NULL; s_cell = s_cell->GetNextShape())
	{
		for (CVertex* v_cell = s_cell->GetVertexHead(); v_cell != NULL; v_cell = v_cell->GetNextVertex())
		{
			float dis = 0.0f;

			dis = pow(v_cell->GetX() - Press_x, 2) + pow(v_cell->GetY() - Press_y, 2);
			dis = sqrt(dis);

			if (dis <= 0.05)
			{
				if (select_vertex != NULL)	
				{
					float tmp_dis = 0.0f;

					tmp_dis = pow(select_vertex->GetX() - Press_x, 2) + pow(select_vertex->GetY() - Press_y, 2);
					tmp_dis = sqrt(tmp_dis);

					if (tmp_dis < dis)	continue;
				}

				select_vertex = v_cell;
				select_linestart = NULL;
				select_lineend = NULL;
				select_shape = NULL;
			}
		}
	}
}

// 稜線の選択
void CAdminControl::SelectLine(float Press_x, float Press_y)
{
	// TODO: ここに実装コードを追加します.
	// 初期化
	select_linestart = NULL;	select_lineend = NULL;
	for (CShape* s_cell = shape_head; s_cell != NULL; s_cell = s_cell->GetNextShape())
	{
		for (CVertex* v_cell = s_cell->GetVertexHead(); v_cell != NULL; v_cell = v_cell->GetNextVertex())
		{
			CVertex line, clickToend;
			CVertex* line_s = NULL;
			CVertex* line_e = NULL;
			float s = 0.0f;

			clickToend.SetXY(Press_x - v_cell->GetX(), Press_y - v_cell->GetY());

			if (v_cell->GetNextVertex() != NULL)
			{
				line_s = v_cell;	line_e = v_cell->GetNextVertex();
			}
			else if (s_cell->GetShapeCloseFlag())
			{
				line_s = v_cell;	line_e = s_cell->GetVertexHead();
			}
			line.SetXY(line_s->GetX() - line_e->GetX(), line_s->GetY() - line_e->GetY());
			clickToend.SetXY(Press_x - line_e->GetX(), Press_y - line_e->GetY());

			s = (clickToend.GetX() * line.GetX() + clickToend.GetY() * line.GetY()) / 
				(line.GetX() * line.GetX() + line.GetY() * line.GetY());

			// 稜線の距離を計算
			if (s >= 0 && s <= 1)
			{
				float d = 0.0;
				CVertex clickTostart;
				clickTostart.SetXY(Press_x - line_s->GetX(), Press_y - line_s->GetY());

				d = abs(clickTostart.GetX() * line.GetY() - clickTostart.GetY() * line.GetX()) /
					sqrt(pow(line.GetX(), 2) + pow(line.GetY(), 2));

				if (d <= 0.05)
				{
					float tmp_d = 0.0f;

					if (select_linestart != NULL)
					{
						CVertex tmp_line, tmp_clickTostart;

						tmp_line.SetXY(select_linestart->GetX() - select_lineend->GetX(), select_linestart->GetY() - select_lineend->GetY());
						tmp_clickTostart.SetXY(Press_x - select_linestart->GetX(), Press_y - select_linestart->GetY());

						tmp_d = tmp_clickTostart.GetX() * tmp_line.GetY() - tmp_clickTostart.GetY() * tmp_line.GetX() /
							sqrt(pow(tmp_line.GetX(), 2) + pow(tmp_line.GetY(), 2));

						if (tmp_d <= d)	continue;
					}

					select_linestart = line_s;
					select_lineend = line_e;
					select_vertex = NULL;
					select_shape = NULL;

				}
			}
		}
	}
}


// 形状選択
void CAdminControl::SelectShape(float Press_x, float Press_y)
{
	// TODO: ここに実装コードを追加します.
	select_shape = NULL;
	for (CShape* s_cell = shape_head; s_cell != NULL; s_cell = s_cell->GetNextShape())
	{
		if (s_cell->Insection_Judge(Press_x, Press_y))
		{
			select_shape = s_cell;
			select_vertex = NULL;
			select_linestart = NULL;
			select_lineend = NULL;
		}
	}
}
