// MyDialog.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "syaku8.h"
#include "MyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDialog �_�C�A���O


CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
	Create(CMyDialog::IDD,pParent);
}


void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	//{{AFX_MSG_MAP(CMyDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialog ���b�Z�[�W �n���h��

void CMyDialog::OnOK() 
{
	DestroyWindow();	
//	CDialog::OnOK();
}

void CMyDialog::OnCancel() 
{
	DestroyWindow();	
//	CDialog::OnCancel();
}

void CMyDialog::PostNcDestroy() 
{
	delete this;	
//	CDialog::PostNcDestroy();
}
