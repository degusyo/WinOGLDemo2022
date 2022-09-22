#pragma once
class CVertex
{
public:
	CVertex();
	~CVertex();
private:
	// x座標
	float x;
	// y座標
	float y;
	// 次の点
	CVertex* next;
public:
	// 座標格納
	void SetXY(float new_x, float new_y);
	// x座標返却
	float GetX();
	// y座標返却
	float GetY();
	// 次の点を格納
	void SetNextVertex(CVertex* next_v);
	// 次の点のポインタを返却
	CVertex* GetNextVertex();
};

