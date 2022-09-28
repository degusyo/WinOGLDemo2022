#include "pch.h"
#include "CAdminControl.h"

CAdminControl::CAdminControl()
{
}

CAdminControl::~CAdminControl()
{
}


// 描画関数
void CAdminControl::Draw()
{
	// TODO: ここに実装コードを追加します.
	// 問8.2
	CVertex cell;
	cell.SetXY(LPress_x, LPress_y);

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(cell.GetX(), cell.GetY());
	glEnd();
}


// 左押し込み座標格納
void CAdminControl::SetLPress_XY(float x, float y)
{
	// TODO: ここに実装コードを追加します.
	LPress_x = x;
	LPress_y = y;
}
