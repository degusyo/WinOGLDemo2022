
// WinOGLDemo2022View.cpp : CWinOGLDemo2022View クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "WinOGLDemo2022.h"
#endif

#include "WinOGLDemo2022Doc.h"
#include "WinOGLDemo2022View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinOGLDemo2022View

IMPLEMENT_DYNCREATE(CWinOGLDemo2022View, CView)

BEGIN_MESSAGE_MAP(CWinOGLDemo2022View, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CWinOGLDemo2022View コンストラクション/デストラクション

CWinOGLDemo2022View::CWinOGLDemo2022View() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CWinOGLDemo2022View::~CWinOGLDemo2022View()
{
}

BOOL CWinOGLDemo2022View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CWinOGLDemo2022View 描画

// ウィンドウ再描画
void CWinOGLDemo2022View::OnDraw(CDC* pDC)
{
	CWinOGLDemo2022Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	wglMakeCurrent(pDC->m_hDC, m_hRC);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(pDC->m_hDC, NULL);
}


// CWinOGLDemo2022View の診断

#ifdef _DEBUG
void CWinOGLDemo2022View::AssertValid() const
{
	CView::AssertValid();
}

void CWinOGLDemo2022View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinOGLDemo2022Doc* CWinOGLDemo2022View::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinOGLDemo2022Doc)));
	return (CWinOGLDemo2022Doc*)m_pDocument;
}
#endif //_DEBUG


// CWinOGLDemo2022View メッセージ ハンドラー


void CWinOGLDemo2022View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	CView::OnLButtonDown(nFlags, point);
}

// ウィンドウ表示
int CWinOGLDemo2022View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: ここに特定な作成コードを追加してください。
	PIXELFORMATDESCRIPTOR pfd =
	{
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW |
	PFD_SUPPORT_OPENGL |
	PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	32,
	0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	24,
	0,0,
	PFD_MAIN_PLANE,
	0,
	0,0,0
	};
	CClientDC clientDC(this);
	int pixelFormat = ChoosePixelFormat(clientDC.m_hDC,
		&pfd);
	SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);

	return 0;
}

// ウィンドウ削除
void CWinOGLDemo2022View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	wglDeleteContext(m_hRC);

}
