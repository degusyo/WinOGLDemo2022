#pragma once
#include "gl/GL.h" // �Y��Ȃ��I�I
#include "CVertex.h"

class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();
	// �`��֐�
	void Draw();
private:
	// ����������x���W
	float LPress_x;
	// ����������y���W
	float LPress_y;
public:
	// ���������ݍ��W�i�[
	void SetLPress_XY(float x, float y);
};

