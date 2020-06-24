// SaveData.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CSaveData �_�C�A���O


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
// CSaveData ���b�Z�[�W �n���h��

BOOL CSaveData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_EDITWN)->SetFocus();
	
	return FALSE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}
