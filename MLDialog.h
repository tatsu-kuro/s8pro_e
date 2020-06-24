#if !defined(AFX_MLDIALOG_H__5DD42661_03FF_42FC_910E_AB79023F8DF9__INCLUDED_)
#define AFX_MLDIALOG_H__5DD42661_03FF_42FC_910E_AB79023F8DF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MLDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CMLDialog ダイアログ

class CMLDialog : public CDialog
{
// コンストラクション
public:
	CMLDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CMLDialog)
	enum { IDD = IDD_MODELESS };
	CListBox	m_help;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMLDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMLDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MLDIALOG_H__5DD42661_03FF_42FC_910E_AB79023F8DF9__INCLUDED_)
