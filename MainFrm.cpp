// MainFrm.cpp : CMainFrame �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "Syaku8.h"
#include "tuner.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern DATADP DP;
int csx,csy;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame �N���X�̍\�z/����

CMainFrame::CMainFrame()
{
	// TODO: ���̈ʒu�Ƀ����o�̏����������R�[�h��ǉ����Ă��������B
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	int size=GetSystemMetrics(SM_CYMENU);//��s�̃��~���[�o�[����
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		     | WS_SYSMENU | WS_MINIMIZEBOX;
	csx=cs.cx=770;
	if(size==20||size==25)cs.cy=6+534+size*2;
	else cs.cy=534+size*2;
	csy=cs.cy;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame �N���X�̐f�f

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame ���b�Z�[�W �n���h��



void CMainFrame::OnHelp() 
{
	myDlg=new CMLDialog(this);	
}

void CMainFrame::OnDestroy() 
{
	WINDOWPLACEMENT wndPlace;
	wndPlace.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&wndPlace);
//	sprintf(ptxt[WINXY],"%d,%d,%d,%d",
	DP.winx1=	wndPlace.rcNormalPosition.left,
	DP.winy1=	wndPlace.rcNormalPosition.top,
	DP.winx2=	DP.winx1+csx;//wndPlace.rcNormalPosition.right,
	DP.winy2=	DP.winy1+csy;//wndPlace.rcNormalPosition.bottom,
//		wndPlace.showCmd==SW_SHOWMAXIMIZED ? 1:0);
	CFrameWnd::OnDestroy();
}
