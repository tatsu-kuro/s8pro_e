#if !defined(AFX_SAVEDATA_H__A5E6F300_6567_11D4_AF4F_E4A8818A9EA4__INCLUDED_)
#define AFX_SAVEDATA_H__A5E6F300_6567_11D4_AF4F_E4A8818A9EA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveData.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSaveData ダイアログ

class CSaveData : public CDialog
{
// コンストラクション
public:
	CSaveData(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSaveData)
	enum { IDD = IDC_WAVENAME };
	CString	m_WAVENAME;
	CString	m_title;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSaveData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSaveData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SAVEDATA_H__A5E6F300_6567_11D4_AF4F_E4A8818A9EA4__INCLUDED_)
