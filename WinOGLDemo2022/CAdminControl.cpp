#include "pch.h"
#include "CAdminControl.h"

CAdminControl::CAdminControl()
{
}

CAdminControl::~CAdminControl()
{
}


// •`‰æŠÖ”
void CAdminControl::Draw(float x, float y)
{
	// TODO: ‚±‚±‚ÉÀ‘•ƒR[ƒh‚ğ’Ç‰Á‚µ‚Ü‚·.
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();

}
