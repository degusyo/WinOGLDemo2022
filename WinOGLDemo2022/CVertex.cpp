#include "pch.h"
#include "CVertex.h"

CVertex::CVertex()
{
}

CVertex::~CVertex()
{
}


// ���W�i�[
void CVertex::SetXY(float new_x, float new_y)
{
    // TODO: �����Ɏ����R�[�h��ǉ����܂�.
    x = new_x;
    y = new_y;
}


// x���W�ԋp
float CVertex::GetX()
{
    // TODO: �����Ɏ����R�[�h��ǉ����܂�.
    return x;
}


// y���W�ԋp
float CVertex::GetY()
{
    // TODO: �����Ɏ����R�[�h��ǉ����܂�.
    return y;
}


// ���̓_���i�[
void CVertex::SetNextVertex(CVertex* next_v)
{
    // TODO: �����Ɏ����R�[�h��ǉ����܂�.
    next = next_v;
}


// ���̓_�̃|�C���^��ԋp
CVertex* CVertex::GetNextVertex()
{
    // TODO: �����Ɏ����R�[�h��ǉ����܂�.
    return next;
}
