// RecvFileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LANTalk.h"
#include "RecvFileDlg.h"
#include "afxdialogex.h"


// CRecvFileDlg 对话框

IMPLEMENT_DYNAMIC(CRecvFileDlg, CDialogEx)

CRecvFileDlg::CRecvFileDlg(CWnd * pParent /*=NULL*/)
	: CDialogEx(IDD_RECEIVE_FILE, pParent)
	, fileName(_T(""))
	, showInfo(_T(""))
	, defaultDir(_T(""))
	, saveFolderPath(_T(""))
{

}

CRecvFileDlg::CRecvFileDlg(CString _fileName, CString _showInfo, CWnd * pParent /*=NULL*/)
	: CDialogEx(IDD_RECEIVE_FILE, pParent)
	, fileName(_fileName)
	, showInfo(_showInfo)
	, defaultDir(_T(""))
	, saveFolderPath(_T(""))
{
}


CRecvFileDlg::~CRecvFileDlg()
{
}

void CRecvFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_INFO, m_static);
	DDX_Control(pDX, IDC_ACCEPT, m_accept);
	DDX_Control(pDX, IDC_NOT_ACCEPT, m_refuse);
}


BEGIN_MESSAGE_MAP(CRecvFileDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ACCEPT, &CRecvFileDlg::OnBnClickedAccept)
	ON_BN_CLICKED(IDC_NOT_ACCEPT, &CRecvFileDlg::OnBnClickedNotAccept)
END_MESSAGE_MAP()


// CRecvFileDlg 消息处理程序


void CRecvFileDlg::OnBnClickedAccept()
{
	// TODO: 在此添加控件通知处理程序代码
	//
	CString filter = L"";//L"文件 (*.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls||";   //文件过虑的类型  
	if (L"" == defaultDir) {
		CString  tmp;
		tmp.LoadString(DEFAULT_DIR);
		defaultDir.Format(tmp, CString(theApp.sInfo.name));
	}
	CFileDialog openFileDlg(FALSE, defaultDir, fileName,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter,NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + L"\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
		saveFolderPath = openFileDlg.GetFolderPath();
		defaultDir = saveFolderPath;
	}
	else {
		saveFolderPath = L"";
	}
	//AfxMessageBox(filePath + L"\r\n" + openFileDlg.GetFolderPath()
		//+ L"\r\n" + openFileDlg.GetFileTitle());//For debug use
	//close dialog;
	CDialog::OnOK();
}



void CRecvFileDlg::OnBnClickedNotAccept()
{
	// TODO: 在此添加控件通知处理程序代码
	saveFolderPath = L"";
	//close dialog
	CDialog::OnCancel();
}


BOOL CRecvFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	showInfo += L" Do you want to accept it?";
	SetDlgItemTextW(IDC_FILE_INFO, showInfo);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
