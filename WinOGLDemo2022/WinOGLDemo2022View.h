
// WinOGLDemo2022View.h : CWinOGLDemo2022View クラスのインターフェイス
//

#pragma once
#include "CAdminControl.h"


class CWinOGLDemo2022View : public CView
{
protected: // シリアル化からのみ作成します。
	CWinOGLDemo2022View() noexcept;
	DECLARE_DYNCREATE(CWinOGLDemo2022View)

// 属性
public:
	CWinOGLDemo2022Doc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CWinOGLDemo2022View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	HGLRC m_hRC;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	// 左押し込みx座標
	float LPress_x;
	// 左押し込みy座標
	float LPress_y;
	// マウスX座標
	float Move_x;
	// マウスY座標
	float Move_y;
	// Adminクラス呼び出し変数
	CAdminControl AC;
public:
	afx_msg void OnXyz();
	afx_msg void OnUpdateXyz(CCmdUI* pCmdUI);
	afx_msg void OnEdit();
	afx_msg void OnUpdateEdit(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // WinOGLDemo2022View.cpp のデバッグ バージョン
inline CWinOGLDemo2022Doc* CWinOGLDemo2022View::GetDocument() const
   { return reinterpret_cast<CWinOGLDemo2022Doc*>(m_pDocument); }
#endif

