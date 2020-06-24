// SaveData.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "Syaku8.h"
#include "SaveData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveData ダイアログ


CSaveData::CSaveData(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveData)
	m_WAVENAME = _T("");
	m_title = _T("");
	//}}AFX_DATA_INIT
}


void CSaveData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveData)
	DDX_Text(pDX, IDC_EDITWN, m_WAVENAME);
	DDV_MaxChars(pDX, m_WAVENAME, 40);
	DDX_Text(pDX, IDC_DATATITLE, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveData, CDialog)
	//{{AFX_MSG_MAP(CSaveData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveData メッセージ ハンドラ

BOOL CSaveData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_EDITWN)->SetFocus();
	
	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
