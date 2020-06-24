#if !defined(AFX_MYDIALOG_H__615E0C9F_5C50_4F47_8AF7_9148BBCEB113__INCLUDED_)
#define AFX_MYDIALOG_H__615E0C9F_5C50_4F47_8AF7_9148BBCEB113__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CMyDialog ダイアログ

class CMyDialog : public CDialog
{
// コンストラクション
public:
	CMyDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CMyDialog)
	enum { IDD = IDD_DIALOG1 };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMyDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMyDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MYDIALOG_H__615E0C9F_5C50_4F47_8AF7_9148BBCEB113__INCLUDED_)
