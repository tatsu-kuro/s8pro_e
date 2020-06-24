// MainFrm.cpp : CMainFrame クラスの動作の定義を行います。
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
// CMainFrame クラスの構築/消滅

CMainFrame::CMainFrame()
{
	// TODO: この位置にメンバの初期化処理コードを追加してください。
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	int size=GetSystemMetrics(SM_CYMENU);//一行のメミューバー高さ
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		     | WS_SYSMENU | WS_MINIMIZEBOX;
	csx=cs.cx=770;
	if(size==20||size==25)cs.cy=6+534+size*2;
	else cs.cy=534+size*2;
	csy=cs.cy;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの診断

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
// CMainFrame メッセージ ハンドラ



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
