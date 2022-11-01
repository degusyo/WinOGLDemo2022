#pragma once
#include "gl/GL.h" // �Y��Ȃ��I�I
#include "CVertex.h"
#include "CShape.h"
#include "math.h"

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
	// �����
	bool Insection_Judge(float x, float y);
	void DrawAxis();
	// XYZ���t���O
	bool AxisFlag;
private:
	// �ҏW���[�h�t���O
	bool EditFlag;
public:
	// �ҏW�t���O�ؑ�
	void ChangeEditFlag();
	// �ҏW�t���O�ԋp
	bool GetEditFlag();
private:
	// �I�����ꂽ���_
	CVertex* select_vertex;
	// �I�����ꂽ�����̊J�n�_
	CVertex* select_linestart;
	// �I�����ꂽ�����̏I���_
	CVertex* select_lineend;
	// �I�����ꂽ�}�`
	CShape* select_shape;
	// ���_�̑I��
	void SelectVertex(float Press_x, float Press_y);
	// �Ő��̑I��
	void SelectLine(float Press_x, float Press_y);
public:
	// �ҏW
	void Edit(float Press_x, float Press_y);
	// �I���E�ҏW���e��`��
	void EditDraw();
	// �`��I��
	void SelectShape(float Press_x, float Press_y);
};

