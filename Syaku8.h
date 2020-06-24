// Syaku8.h : SYAKU8 アプリケーションのメイン ヘッダー ファイル
//

#if !defined(AFX_SYAKU8_H__2184B4C4_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_)
#define AFX_SYAKU8_H__2184B4C4_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CSyaku8App:
// このクラスの動作の定義に関しては Syaku8.cpp ファイルを参照してください。
//

class CSyaku8App : public CWinApp
{
public:
	CSyaku8App();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSyaku8App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CSyaku8App)
//	afx_msg void OnAppAbout();
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SYAKU8_H__2184B4C4_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_)
