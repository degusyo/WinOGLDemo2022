
// WinOGLDemo2022.h : WinOGLDemo2022 アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル
#include "gl/GL.h"


// CWinOGLDemo2022App:
// このクラスの実装については、WinOGLDemo2022.cpp を参照してください
//

class CWinOGLDemo2022App : public CWinApp
{
public:
	CWinOGLDemo2022App() noexcept;


// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWinOGLDemo2022App theApp;
