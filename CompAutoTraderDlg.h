// CompAutoTraderDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_COMPAUTOTRADERDLG_H__FFF9CDF7_70B0_4184_8CBF_889745605C31__INCLUDED_)
#define AFX_COMPAUTOTRADERDLG_H__FFF9CDF7_70B0_4184_8CBF_889745605C31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCompAutoTraderDlg �_�C�A���O

class CCompAutoTraderDlg : public CDialog
{
// �\�z
public:
	CCompAutoTraderDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CCompAutoTraderDlg)
	enum { IDD = IDD_COMPAUTOTRADER_DIALOG };
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CCompAutoTraderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CCompAutoTraderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CString GetLastErrorMessage(DWORD dwLastError = NULL);
CString GetExceptionErrorMessage(CException* pEx);
void PumpWaitingMessages();
int CreateGuid(CString& strGuid);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_COMPAUTOTRADERDLG_H__FFF9CDF7_70B0_4184_8CBF_889745605C31__INCLUDED_)
