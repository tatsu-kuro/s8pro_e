#if !defined(AFX_SAVEDATA_H__A5E6F300_6567_11D4_AF4F_E4A8818A9EA4__INCLUDED_)
#define AFX_SAVEDATA_H__A5E6F300_6567_11D4_AF4F_E4A8818A9EA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveData.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSaveData �_�C�A���O

class CSaveData : public CDialog
{
// �R���X�g���N�V����
public:
	CSaveData(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSaveData)
	enum { IDD = IDC_WAVENAME };
	CString	m_WAVENAME;
	CString	m_title;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSaveData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSaveData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SAVEDATA_H__A5E6F300_6567_11D4_AF4F_E4A8818A9EA4__INCLUDED_)
