#include "pch.h"
#include "CAdminControl.h"

CAdminControl::CAdminControl()
{
}

CAdminControl::~CAdminControl()
{
}


// �`��֐�
void CAdminControl::Draw(float x, float y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();

}
