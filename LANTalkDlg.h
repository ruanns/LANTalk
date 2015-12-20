
// LANTalkDlg.h : header file
//

#pragma once
#include "ChatDlg.h"
#include "LanSelDlg.h"
#include "ChatToolBar.h"


// CLANTalkDlg dialog
class CLANTalkDlg : public CDialogEx
{
// Construction
public:
	CLANTalkDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LANTALK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	LanSelDlg m_lan;
	CChatDlg m_chat;
	CChatToolBar m_tool;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	int SendMsg(CString sIP, CString MyMsg);
	void InsertUser(CString UserName, CString HostName, CString IP, CString Mark);
	CChatDlg * GetChatDlg();

	int deleteUser(CString ip);
};
