#include "pch.h"
#include "CAdminControl.h"

CAdminControl::CAdminControl()
{
}

CAdminControl::~CAdminControl()
{
}


// �`��֐�
void CAdminControl::Draw()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	// ��8.2
	CVertex v1, v2, v3, v4;
	v1.SetXY(-0.5, 0.5);
	v1.SetNextVertex(&v2);
	v2.SetXY(-0.5, -0.5);
	v2.SetNextVertex(&v3);
	v3.SetXY(0.5, -0.5);
	v3.SetNextVertex(&v4);
	v4.SetXY(0.5, 0.5);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);

	for (CVertex* cell = &v1; cell != NULL; cell = cell->GetNextVertex())
	{
		glVertex2f(cell->GetX(), cell->GetY());
	}
	glEnd();
}


// ���������ݍ��W�i�[
void CAdminControl::SetLPress_XY(float x, float y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	LPress_x = x;
	LPress_y = y;
}
