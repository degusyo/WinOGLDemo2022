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
