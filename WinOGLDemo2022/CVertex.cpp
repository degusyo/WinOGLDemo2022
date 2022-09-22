#include "pch.h"
#include "CVertex.h"

CVertex::CVertex()
{
}

CVertex::~CVertex()
{
}


// 座標格納
void CVertex::SetXY(float new_x, float new_y)
{
    // TODO: ここに実装コードを追加します.
    x = new_x;
    y = new_y;
}


// x座標返却
float CVertex::GetX()
{
    // TODO: ここに実装コードを追加します.
    return x;
}


// y座標返却
float CVertex::GetY()
{
    // TODO: ここに実装コードを追加します.
    return y;
}


// 次の点を格納
void CVertex::SetNextVertex(CVertex* next_v)
{
    // TODO: ここに実装コードを追加します.
    next = next_v;
}


// 次の点のポインタを返却
CVertex* CVertex::GetNextVertex()
{
    // TODO: ここに実装コードを追加します.
    return next;
}
