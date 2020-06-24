// Syaku8Doc.cpp : CSyaku8Doc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "Syaku8.h"

#include "Syaku8Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSyaku8Doc

IMPLEMENT_DYNCREATE(CSyaku8Doc, CDocument)

BEGIN_MESSAGE_MAP(CSyaku8Doc, CDocument)
	//{{AFX_MSG_MAP(CSyaku8Doc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyaku8Doc クラスの構築/消滅

CSyaku8Doc::CSyaku8Doc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CSyaku8Doc::~CSyaku8Doc()
{
}

BOOL CSyaku8Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSyaku8Doc シリアライゼーション

void CSyaku8Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSyaku8Doc クラスの診断

#ifdef _DEBUG
void CSyaku8Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSyaku8Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSyaku8Doc コマンド
