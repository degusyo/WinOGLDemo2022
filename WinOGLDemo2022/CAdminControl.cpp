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


// �`��֐�
void CAdminControl::Draw()
{
	if (AxisFlag) {
		DrawAxis();
	}

	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	for (CShape* s = shape_head; s != NULL; s = s->GetNextShape())
	{
		for (CVertex* v = s->GetVertexHead(); v != NULL; v = v->GetNextVertex())
		{
			// �_�̕`��
			glColor3f(1.0, 1.0, 1.0);
			glPointSize(15);
			glBegin(GL_POINTS);
			glVertex2f(v->GetX(), v->GetY());
			glEnd();

			// ���̕`��
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

// �I���E�ҏW���e��`��
void CAdminControl::EditDraw()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	if (select_vertex != NULL)
	{
		// �_�̕`��
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

// ���������ݍ��W�i�[
void CAdminControl::SetLPress_XY(float x, float y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	LPress_x = x;
	LPress_y = y;
}


// ���_�ǉ�
void CAdminControl::NewSetVertex(float new_x, float new_y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	// �쐬���̌`�󂪂Ȃ�������
	if (!Insection_Judge(new_x, new_y))
	{
		if (shape_head == NULL || shape_head->GetShapeCloseFlag())
		{
			CShape* new_shape = new CShape;

			// ��ڂ̌`��
			if (shape_head != NULL)
			{
				new_shape->SetNextShape(shape_head);
			}
			shape_head = new_shape;

			// ���_�ǉ�
			shape_head->SetNewVertex(new_x, new_y);
		}
		else
		{
			// �`�����邩�̔���
			if (shape_head->GetVertexCount() > 2)
			{
				// �[�_�Ƃ̋����v�Z
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


// Shape�̃������J��
void CAdminControl::DeleteShape()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	while (shape_head != NULL)
	{
		CShape* del_s;
		del_s = shape_head;
		shape_head = shape_head->GetNextShape();

		delete del_s;
	}
}




// ����������
bool CAdminControl::CrossCheckOut(CVertex* start_v, CVertex* end_v)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	for (CShape* s = shape_head; s != NULL; s = s->GetNextShape())
	{
		if (!s->CrossCheckIn(start_v, end_v))	return false;
	}

	return true;
}


// �����
bool CAdminControl::Insection_Judge(float x, float y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	for (CShape* s_cell = shape_head; s_cell != NULL; s_cell = s_cell->GetNextShape())
	{
		if (s_cell->GetShapeCloseFlag() && s_cell->Insection_Judge(x, y))	return true;
	}

	return false;
}


void CAdminControl::DrawAxis()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	glBegin(GL_LINES);
	// x��
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	// y��
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	// z��
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
}


// �ҏW�t���O�ؑ�
void CAdminControl::ChangeEditFlag()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	if (EditFlag)
	{
		EditFlag = false;
	}
	else
	{
		EditFlag = true;
	}
}


// �ҏW�t���O�ԋp
bool CAdminControl::GetEditFlag()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	return EditFlag;
}


// �ҏW
void CAdminControl::Edit(float Press_x, float Press_y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	
	// �_�̑I��
	SelectVertex(Press_x, Press_y);
	

	// ���̑I��
	if (select_vertex == NULL) 
	{
		SelectLine(Press_x, Press_y);
	}

	// �`��̑I��
	if (select_linestart == NULL)
	{
		SelectShape(Press_x, Press_y);
	}

}

// ���_�̑I��
void CAdminControl::SelectVertex(float Press_x, float Press_y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
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

// �Ő��̑I��
void CAdminControl::SelectLine(float Press_x, float Press_y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	// ������
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

			// �Ő��̋������v�Z
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


// �`��I��
void CAdminControl::SelectShape(float Press_x, float Press_y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
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
