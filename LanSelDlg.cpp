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
	ON_NOTIFY(NM_CLICK, IDC_LIST_LAN, &LanSelDlg::OnNMClickListLan)
	ON_BN_CLICKED(IDOK, &LanSelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// LanSelDlg 消息处理程序
int LanSelDlg::InitialLanSelList()
{
	m_lanSel.InsertColumn(0, L"网络适配器名称", LVCFMT_LEFT, 150, -1);
	m_lanSel.InsertColumn(1, L"IP 地址", LVCFMT_LEFT, 150, -1);
	m_lanSel.InsertColumn(2, L"子网掩码", LVCFMT_LEFT, 150, -1);
	//m_lanSel.InsertColumn(3, L"MASK", LVCFMT_LEFT, 100, -1);

	DWORD dwStyle = m_lanSel.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_CHECKBOXES;
	m_lanSel.SetExtendedStyle(dwStyle);

	return 0;
}


void LanSelDlg::OnNMClickListLan(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nSel = pNMItemActivate->iItem;
	if (nSel < 0){
		return;
	}
	else {
		CString str;
		str = L"\t" + m_lanSel.GetItemText(nSel, 0) +L"\t"
			+ m_lanSel.GetItemText(nSel, 1)+L"\t"
			+ m_lanSel.GetItemText(nSel, 2)+L"\r\n"
			+L" is selected. Please click OK to continue.";
		SetDlgItemText(IDC_STATIC, str);
		theApp.netMode = nSel;
	}
	*pResult = 0;
}


void LanSelDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (-1 == theApp.netMode) {
		CString str, tmp;
		GetDlgItemText(IDC_STATIC, str);
		tmp.Format(L"\t%d \r\nYou Must Select one net mode that you are using!", theApp.netMode);
		AfxMessageBox(str + tmp);
		return;
	}	
	CDialog::OnOK();
}


int LanSelDlg::insertLanmode(CString modeName, CString ip, CString mark)
{
	if (L"" == modeName || L"" == ip || L"" == mark) {
		AfxMessageBox(L"Erroe happened when initial the network parameters");
		return -1;
	}
	int pos = m_lanSel.GetItemCount() + 1;
	m_lanSel.InsertItem(LVIF_TEXT | LVIF_STATE, pos, modeName,
		(pos % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0);
	m_lanSel.SetItemText(pos, 0, modeName);
	m_lanSel.SetItemText(pos, 1, ip);
	m_lanSel.SetItemText(pos, 2, mark);

	return 0;
}
