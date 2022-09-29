#pragma once
#include "gl/GL.h" // �Y��Ȃ��I�I
#include "CVertex.h"
#include "CShape.h"

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
	// Shape���X�g�̐擪
	CShape* shape_head;
public:
	// ���������ݍ��W�i�[
	void SetLPress_XY(float x, float y);
	// ���_�ǉ�
	void NewSetVertex(float new_x, float new_y);
	// Shape�̃������J��
	void DeleteShape();
	// ����������
	bool CrossCheckOut(CVertex* start_v, CVertex* end_v);
};

