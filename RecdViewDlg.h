#pragma once
#include "afxwin.h"


// CRecdViewDlg 对话框

class CRecdViewDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecdViewDlg)

public:
	CRecdViewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRecdViewDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECD_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_viewRecd;
};
