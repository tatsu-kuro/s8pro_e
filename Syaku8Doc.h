// Syaku8Doc.h : CSyaku8Doc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYAKU8DOC_H__2184B4CA_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_)
#define AFX_SYAKU8DOC_H__2184B4CA_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSyaku8Doc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CSyaku8Doc();
	DECLARE_DYNCREATE(CSyaku8Doc)

// アトリビュート
public:

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSyaku8Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CSyaku8Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CSyaku8Doc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SYAKU8DOC_H__2184B4CA_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_)
