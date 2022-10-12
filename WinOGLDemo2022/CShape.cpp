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


// �V�����_�̐ݒ�
void CShape::SetNewVertex(float new_x, float new_y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.

	//�V�������_����
	CVertex* new_vertex = new CVertex;
	vertex_cnt++;

	// ���W�i�[
	new_vertex->SetXY(new_x, new_y);

	// ���X�g�A���C��
	if (vertex_cnt > 1)
	{
		new_vertex->SetNextVertex(vertex_head);
	}
	vertex_head = new_vertex;
}


// ���_���X�g�̒[�_��Ԃ�
CVertex* CShape::GetVertexHead()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	return vertex_head;
}


// ���_����ԋp
int CShape::GetVertexCount()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	return vertex_cnt;
}


// �`��̕������̔���ԋp
bool CShape::GetShapeCloseFlag()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	return close_flag;
}


// �`������
void CShape::CloseShape()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	close_flag = true;
}


// next_shape�Ɏ���Shape����i�[
void CShape::SetNextShape(CShape* next_s)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	next_shape = next_s;
}


// ����Shape��ԋp
CShape* CShape::GetNextShape()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	return next_shape;
}


// vertex�̃������J��
void CShape::DeleteVertex()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	while (vertex_head != NULL)
	{
		CVertex* del_v;
		del_v = vertex_head;
		vertex_head = vertex_head->GetNextVertex();

		delete del_v;
	}
}


// ��������
bool CShape::CrossCheckIn(CVertex* start_v, CVertex* end_v)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	for (CVertex* v = vertex_head; v != NULL; v = v->GetNextVertex())
	{
		// �������肷��_��ݒ�
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

		// �x�N�g�������߂�
		CVertex a, b, a1, a2, b1, b2;
		a.SetXY(a_e->GetX() - a_s->GetX(), a_e->GetY() - a_s->GetY());
		b.SetXY(b_e->GetX() - b_s->GetX(), b_e->GetY() - b_s->GetY());
		a1.SetXY(b_s->GetX() - a_s->GetX(), b_s->GetY() - a_s->GetY());
		a2.SetXY(b_e->GetX() - a_s->GetX(), b_e->GetY() - a_s->GetY());
		b1.SetXY(a_s->GetX() - b_s->GetX(), a_s->GetY() - b_s->GetY());
		b2.SetXY(a_e->GetX() - b_s->GetX(), a_e->GetY() - b_s->GetY());

		 // ��������
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


// �����
bool CShape::Insection_Judge(float x, float y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	float n = 0.0f;
	for (CVertex* v_cell = vertex_head; v_cell != NULL; v_cell = v_cell->GetNextVertex())
	{
		CVertex a, b;

		if (v_cell->GetNextVertex() != NULL)
		{
			// �x�N�g���̎Z�o
			a.SetXY(v_cell->GetX() - x, v_cell->GetY() - y);
			b.SetXY(v_cell->GetNextVertex()->GetX() - x, v_cell->GetNextVertex()->GetY() - y);
		}
		else
		{
			a.SetXY(v_cell->GetX() - x, v_cell->GetY() - y);
			b.SetXY(vertex_head->GetX() - x, vertex_head->GetY() - y);
		}

		// �O�ρE���ς̌v�Z
		float cross, dot;

		cross = a.GetX() * b.GetY() - a.GetY() * b.GetX();
		dot = a.GetX() * b.GetX() + a.GetY() * b.GetY();

		// �p�x���v�Z
		n += (float)atan2(cross, dot);
	}

	if (abs(n) <= 0.001)	return false;
	return true;
}
