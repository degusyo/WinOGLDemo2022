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
	CVertex cell;
	cell.SetXY(LPress_x, LPress_y);

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(cell.GetX(), cell.GetY());
	glEnd();
}


// ���������ݍ��W�i�[
void CAdminControl::SetLPress_XY(float x, float y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	LPress_x = x;
	LPress_y = y;
}
