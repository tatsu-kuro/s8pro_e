// Syaku8.h : SYAKU8 �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#if !defined(AFX_SYAKU8_H__2184B4C4_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_)
#define AFX_SYAKU8_H__2184B4C4_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CSyaku8App:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� Syaku8.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CSyaku8App : public CWinApp
{
public:
	CSyaku8App();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSyaku8App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	//{{AFX_MSG(CSyaku8App)
//	afx_msg void OnAppAbout();
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SYAKU8_H__2184B4C4_DA36_11D2_8B10_C76FAB0F4F6C__INCLUDED_)
