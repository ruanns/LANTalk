#pragma once
#include "afxcmn.h"

#include "ChatEdit.h"
#include "afxwin.h"



// CChatDlg dialog

class CChatDlg : public CDialog
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = NULL);   // standard constructor
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
	
	EUser* GetCurrentUser();
	void SetCurrentUser(EUser* _user);
	int InitialUserList();
	virtual BOOL OnInitDialog();
	CListCtrl * GetUserListControl();
	
protected:
	CEdit m_message;
	//CChatToolBar m_tool;
public:
//	int InitialtToolBar();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult);
	
};