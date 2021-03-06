#pragma once
#include "afxcmn.h"


// LanSelDlg 对话框

class LanSelDlg : public CDialog
{
	DECLARE_DYNAMIC(LanSelDlg)

public:
	//LanSelDlg(CWnd* pParent = NULL);   // 标准构造函数
	//LanSelDlg(CWnd* pParent = NULL, CString * szIP = NULL,CString * szAdapterName = NULL,CString * szMask = NULL,int AdapterNum = 0);
	LanSelDlg(CWnd* pParent, CString * szIP, CString * szAdapterName, CString * szMask, int AdapterNum);// 标准构造函数
	virtual ~LanSelDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LAN_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CString * szIP;
	CString * szAdapterName;
	CString * szMask;
	int AdapterNum;
	DECLARE_MESSAGE_MAP()
public:
//	int InitialLanSelList();
	CListCtrl m_lanSel;
	afx_msg void OnNMClickListLan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	int insertLanmode(CString modeName, CString ip, CString mark);
	virtual BOOL OnInitDialog();
};
