#pragma once
class CVertex
{
public:
	CVertex();
	~CVertex();
private:
	// x���W
	float x;
	// y���W
	float y;
	// ���̓_
	CVertex* next;
public:
	// ���W�i�[
	void SetXY(float new_x, float new_y);
	// x���W�ԋp
	float GetX();
	// y���W�ԋp
	float GetY();
	// ���̓_���i�[
	void SetNextVertex(CVertex* next_v);
	// ���̓_�̃|�C���^��ԋp
	CVertex* GetNextVertex();
};

