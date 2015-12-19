// LanSelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LANTalk.h"
#include "LanSelDlg.h"
#include "afxdialogex.h"


// LanSelDlg 对话框

IMPLEMENT_DYNAMIC(LanSelDlg, CDialog)

LanSelDlg::LanSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LAN_SELECT, pParent)
{

}

LanSelDlg::~LanSelDlg()
{
}

void LanSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LAN, m_lanSel);
}


BEGIN_MESSAGE_MAP(LanSelDlg, CDialog)
	ON_BN_CLICKED(IDOK, &LanSelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// LanSelDlg 消息处理程序
int LanSelDlg::InitialLanSelList()
{
	m_lanSel.InsertColumn(0, L"网络适配器名称", LVCFMT_LEFT, 150, -1);
	m_lanSel.InsertColumn(1, L"IP 地址", LVCFMT_LEFT, 100, -1);
	m_lanSel.InsertColumn(2, L"子网掩码", LVCFMT_LEFT, 100, -1);
	//m_lanSel.InsertColumn(3, L"MARK", LVCFMT_LEFT, 100, -1);

	DWORD dwStyle = m_lanSel.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_CHECKBOXES;
	m_lanSel.SetExtendedStyle(dwStyle);
	
	int pos = 0;
	m_lanSel.InsertItem(LVIF_TEXT | LVIF_STATE, pos, L"以太网",
		(pos % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0); 
	m_lanSel.SetItemText(pos, 0, L"以太网");
	m_lanSel.SetItemText(pos, 1, L"0.0.0.0");
	m_lanSel.SetItemText(pos, 2, L"255.255.255.0");

	return 0;
}


void LanSelDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	theApp.lanSel = 0 ;
	CDialog::OnOK();
}
