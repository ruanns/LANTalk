// RecdViewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LANTalk.h"
#include "RecdViewDlg.h"
#include "afxdialogex.h"


// CRecdViewDlg 对话框

IMPLEMENT_DYNAMIC(CRecdViewDlg, CDialog)

CRecdViewDlg::CRecdViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_RECD_DLG, pParent)
{

}

CRecdViewDlg::~CRecdViewDlg()
{
}


void CRecdViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIEWRECD, m_viewRecd);
}


BEGIN_MESSAGE_MAP(CRecdViewDlg, CDialog)
END_MESSAGE_MAP()


// CRecdViewDlg 消息处理程序
