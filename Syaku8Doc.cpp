// Syaku8Doc.cpp : CSyaku8Doc �N���X�̓���̒�`���s���܂��B
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyaku8Doc �N���X�̍\�z/����

CSyaku8Doc::CSyaku8Doc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CSyaku8Doc::~CSyaku8Doc()
{
}

BOOL CSyaku8Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSyaku8Doc �V���A���C�[�[�V����

void CSyaku8Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSyaku8Doc �N���X�̐f�f

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
// CSyaku8Doc �R�}���h
