// CompAutoTrader.h : COMPAUTOTRADER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_COMPAUTOTRADER_H__B5A34C2C_6B7F_4643_A1B1_15E39448297E__INCLUDED_)
#define AFX_COMPAUTOTRADER_H__B5A34C2C_6B7F_4643_A1B1_15E39448297E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CCompAutoTraderApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� CompAutoTrader.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CCompAutoTraderApp : public CWinApp
{
public:
	CCompAutoTraderApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CCompAutoTraderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CCompAutoTraderApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_COMPAUTOTRADER_H__B5A34C2C_6B7F_4643_A1B1_15E39448297E__INCLUDED_)
