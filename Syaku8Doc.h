// Syaku8Doc.h : CSyaku8Doc �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYAKU8DOC_H__2184B4CA_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_)
#define AFX_SYAKU8DOC_H__2184B4CA_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSyaku8Doc : public CDocument
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CSyaku8Doc();
	DECLARE_DYNCREATE(CSyaku8Doc)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

//�I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSyaku8Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CSyaku8Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CSyaku8Doc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SYAKU8DOC_H__2184B4CA_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_)
