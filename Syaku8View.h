// Syaku8View.h : CSyaku8View クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYAKU8VIEW_H__2184B4CC_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_)
#define AFX_SYAKU8VIEW_H__2184B4CC_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "MyDialog.h"

class CSyaku8View : public CView
{
protected: // シリアライズ機能のみから作成します。
	CBitmap m_bmp;
	void ComTable(int nani,int n);
	void HidariMigi(CDC* MemDC,CDC* pDC,int n);
//	void DispTBR(CDC* MemDC,CDC *pDC,int top);
	void Dispnow(CDC* MemDC,CDC *pDC);
	void OnReturn1(CDC* MemDC,CDC* pDC);
	void Loadhzdata(CDC* MemDC,CDC *pDC);
	void DoCom(CDC* MemDC,CDC *pDC,int coi,int flag);
	void Butt(CDC* MemDC,CDC* pDC,int i,int flag);
	void DispIroiro(CDC *MemDC,CDC *pDC,int DN,int loca=0,int locan=0);
	CSyaku8View();
	DECLARE_DYNCREATE(CSyaku8View)
// アトリビュート
public:
	CSyaku8Doc* GetDocument();
//	CMyDialog* myDlg;
// オペレーション
public:
//	void DoCom(CDC *pDC,int x);
//	void OnN(int getn);
	void setinst(int inst);

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSyaku8View)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CSyaku8View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CSyaku8View)
	afx_msg void OnUp();
	afx_msg void OnSita();
	afx_msg void OnMigi();
	afx_msg void OnHidari();
	afx_msg void OnReturn();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnShiftret();
	afx_msg void OnCdef();
	afx_msg void OnUpdateCdef(CCmdUI* pCmdUI);
	afx_msg void OnDore();
	afx_msg void OnUpdateDore(CCmdUI* pCmdUI);
	afx_msg void OnFft1();
	afx_msg void OnFft2();
	afx_msg void OnUpdateFft2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFft1(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnA440();
	afx_msg void OnUpdateA440(CCmdUI* pCmdUI);
	afx_msg void OnFft0();
	afx_msg void OnUpdateFft0(CCmdUI* pCmdUI);
	afx_msg void On2700();
	afx_msg void OnUpdate2700(CCmdUI* pCmdUI);
	afx_msg void On5400();
	afx_msg void OnUpdate5400(CCmdUI* pCmdUI);
	afx_msg void OnW0();
	afx_msg void OnUpdateW0(CCmdUI* pCmdUI);
	afx_msg void OnW1();
	afx_msg void OnUpdateW1(CCmdUI* pCmdUI);
	afx_msg void OnW2();
	afx_msg void OnUpdateW2(CCmdUI* pCmdUI);
	afx_msg void On20snt();
	afx_msg void OnUpdate20snt(CCmdUI* pCmdUI);
	afx_msg void On30snt();
	afx_msg void OnUpdate30snt(CCmdUI* pCmdUI);
	afx_msg void On10snt();
	afx_msg void OnUpdate10snt(CCmdUI* pCmdUI);
	afx_msg void OnNoteshz();
	afx_msg void OnUpdateNoteshz(CCmdUI* pCmdUI);
	afx_msg void Onaltosax();
	afx_msg void OnUpdatealtosax(CCmdUI* pCmdUI);
	afx_msg void Onclarinet();
	afx_msg void OnUpdateclarinet(CCmdUI* pCmdUI);
	afx_msg void Onflute();
	afx_msg void OnUpdateflute(CCmdUI* pCmdUI);
	afx_msg void Onfullrange();
	afx_msg void OnUpdatefullrange(CCmdUI* pCmdUI);
	afx_msg void Onhorn();
	afx_msg void OnUpdatehorn(CCmdUI* pCmdUI);
	afx_msg void Onkinko();
	afx_msg void OnUpdatekinko(CCmdUI* pCmdUI);
	afx_msg void Onocarina();
	afx_msg void OnUpdateocarina(CCmdUI* pCmdUI);
	afx_msg void Onrecorder();
	afx_msg void OnUpdaterecorder(CCmdUI* pCmdUI);
	afx_msg void Onsinobue();
	afx_msg void OnUpdatesinobue(CCmdUI* pCmdUI);
	afx_msg void Ontozan();
	afx_msg void OnUpdatetozan(CCmdUI* pCmdUI);
	afx_msg void Ontrombone();
	afx_msg void OnUpdatetrombone(CCmdUI* pCmdUI);
	afx_msg void Ontrumpet();
	afx_msg void OnUpdatetrumpet(CCmdUI* pCmdUI);
	afx_msg void Ontenorsax();
	afx_msg void OnUpdatetenorsax(CCmdUI* pCmdUI);
	afx_msg void Onsopranosax();
	afx_msg void OnUpdatesopranosax(CCmdUI* pCmdUI);
	afx_msg void Onbhorn();
	afx_msg void OnUpdatebhorn(CCmdUI* pCmdUI);
	afx_msg void Onnoukan();
	afx_msg void OnUpdatenoukan(CCmdUI* pCmdUI);
	afx_msg void On00snt();
	afx_msg void OnUpdate00snt(CCmdUI* pCmdUI);
	afx_msg void On10800();
	afx_msg void OnUpdate10800(CCmdUI* pCmdUI);
	afx_msg void OnPagedown();
	afx_msg void OnPageup();
	afx_msg void OnSndcard();
	afx_msg void Onjust();
	afx_msg void OnUpdatejust(CCmdUI* pCmdUI);
	afx_msg void On2700log();
	afx_msg void OnUpdate2700log(CCmdUI* pCmdUI);
	afx_msg void On5400log();
	afx_msg void OnUpdate5400log(CCmdUI* pCmdUI);
	afx_msg void On10800log();
	afx_msg void OnUpdate10800log(CCmdUI* pCmdUI);
	afx_msg void Onoboe();
	afx_msg void OnUpdateoboe(CCmdUI* pCmdUI);
	afx_msg void OnAlta();
	afx_msg void OnS();
	afx_msg void OnJuns8();
	afx_msg void OnUpdateJuns8(CCmdUI* pCmdUI);
	afx_msg void OnC();
	afx_msg void OnNoteshzlimit();
	afx_msg void OnUpdateNoteshzlimit(CCmdUI* pCmdUI);
	afx_msg void Ontin();
	afx_msg void OnUpdatetin(CCmdUI* pCmdUI);
	afx_msg void Onocarina4();
	afx_msg void OnUpdateocarina4(CCmdUI* pCmdUI);
	afx_msg void Onbansuri();
	afx_msg void OnUpdatebansuri(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Syaku8View.cpp ファイルがデバッグ環境の時使用されます。
inline CSyaku8Doc* CSyaku8View::GetDocument()
   { return (CSyaku8Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SYAKU8VIEW_H__2184B4CC_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_)
