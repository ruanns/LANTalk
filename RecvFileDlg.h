#pragma once

#include "afxwin.h"
#include "basicClass.h"


// CRecvFileDlg 对话框

class CRecvFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecvFileDlg)

public:
	CRecvFileDlg(CWnd* pParent = NULL);   // 标准构造函数
	CRecvFileDlg(CString fileName,CString showInfo, CWnd* pParent = NULL);
	virtual ~CRecvFileDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECEIVE_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_static;
	CButton m_accept;
	CButton m_refuse;
	afx_msg void OnBnClickedAccept();
	CString fileName;
	CString saveFolderPath;
	afx_msg void OnBnClickedNotAccept();
	virtual BOOL OnInitDialog();
private:
	CString defaultDir;
	CString showInfo;
};
