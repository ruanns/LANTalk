#pragma once
#include "afxcmn.h"
#include "RecdViewDlg.h"
#include "ChatEdit.h"
#include "afxwin.h"
#include "afxext.h"



// CChatDlg dialog

class CChatDlg : public CDialog
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd * pParent = NULL);   // standard constructor
	virtual ~CChatDlg();

// Dialog Data
	enum { IDD = IDD_CHAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	EUser* pCurrentUser;
	CEdit m_edit;
	//CRichEditCtrl m_message;
	CListCtrl m_user;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	
	int InitialUserList();
	virtual BOOL OnInitDialog();
	CListCtrl * GetUserListControl();
	
protected:
	CRecdViewDlg m_recdDlg;
	CEdit m_message;
	CButton m_button;
	//CChatToolBar m_tool;
public:
//	int InitialtToolBar();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult);
	
	int InsertRecMsg(CString ip, CString msg);
//	afx_msg void OnBnClickedButtonViewrecd();
	afx_msg void OnBnClickedSendFile();
	afx_msg void OnClose();
//	CIconButton m_about;
//	CIconButton m_recdView;
//	CIconButton m_help;
//	CIconButton m_recdView;
//	CIconButton m_reset;
//	CIconButton m_return;
//	CIconButton m_setting;
//	CIconButton m_prog;
//	CStatic m_currentUser;
	CStatic m_showUser;
	CBitmapButton m_about;
	CBitmapButton m_help;
	CBitmapButton m_recdView;
	CBitmapButton m_reset;
	CBitmapButton m_return;
	CBitmapButton m_setting;
	CBitmapButton m_prog;
	CBitmapButton m_sendFile;
	afx_msg void OnEnChangeEditShow();
	afx_msg void OnBnClickedReturn();
//	CButton m_send;
//	CButton m_recd;
	afx_msg void OnBnClickedRecdView();
	CButton m_send;
	CBitmapButton m_head;
	CBitmapButton m_save;
	afx_msg void OnBnClickedSaveRecd();
};
