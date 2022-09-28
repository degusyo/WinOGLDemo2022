#pragma once
#include "CVertex.h"
#include "math.h"

class CShape
{
public:
	CShape();
	~CShape();
	// �V�����_�̐ݒ�
	void SetNewVertex(float new_x, float new_y);
private:
	// vertex���X�g�̍Œ[���w���|�C���^
	CVertex* vertex_head;
	// ���_��
	int vertex_cnt;
	// �`�󂪕��Ă��邩�̔���
	bool close_flag;
public:
	// ���_���X�g�̒[�_��Ԃ�
	CVertex* GetVertexHead();
	// ���_����ԋp
	int GetVertexCount();
	// �`��̕������̔���ԋp
	bool GetShapeCloseFlag();
	// �`������
	void CloseShape();
private:
	// ����Shape�|�C���^
	CShape* next_shape;
public:
	// next_shape�Ɏ���Shape����i�[
	void SetNextShape(CShape* next_s);
	// ����Shape��ԋp
	CShape* GetNextShape();
	// vertex�̃������J��
	void DeleteVertex();
};

