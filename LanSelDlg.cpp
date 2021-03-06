// LanSelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LANTalk.h"
#include "LanSelDlg.h"
#include "afxdialogex.h"


// LanSelDlg 对话框

IMPLEMENT_DYNAMIC(LanSelDlg, CDialog)

LanSelDlg::LanSelDlg(CWnd* pParent = NULL, CString * szIP = NULL, CString * szAdapterName = NULL, CString * szMask = NULL, int AdapterNum = 0)
	: CDialog(IDD_LAN_SELECT, pParent)
{
	this->szIP = szIP;
	this->szAdapterName = szAdapterName;
	this->szMask = szMask;
	this->AdapterNum = AdapterNum;
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
//int LanSelDlg::InitialLanSelList()
//{
//	m_lanSel.InsertColumn(0, L"网络适配器名称", LVCFMT_LEFT, 150, -1);
//	m_lanSel.InsertColumn(1, L"IP 地址", LVCFMT_LEFT, 100, -1);
//	m_lanSel.InsertColumn(2, L"子网掩码", LVCFMT_LEFT, 100, -1);
//	//m_lanSel.InsertColumn(3, L"MARK", LVCFMT_LEFT, 100, -1);
//
//	DWORD dwStyle = m_lanSel.GetExtendedStyle();
//	dwStyle |= LVS_EX_FULLROWSELECT;
//	dwStyle |= LVS_EX_GRIDLINES;
//	dwStyle |= LVS_EX_CHECKBOXES;
//	m_lanSel.SetExtendedStyle(dwStyle);
//	
//	int pos = 0;
//	m_lanSel.InsertItem(LVIF_TEXT | LVIF_STATE, pos, L"以太网",
//		(pos % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0); 
//	m_lanSel.SetItemText(pos, 0, L"以太网");
//	m_lanSel.SetItemText(pos, 1, L"0.0.0.0");
//	m_lanSel.SetItemText(pos, 2, L"255.255.255.0");
//
//	return 0;
//}


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
		str = L"Aadapter Name:" + m_lanSel.GetItemText(nSel, 0) +L"\r\nIP Adress:"
			+ m_lanSel.GetItemText(nSel, 1)+L"\r\n Subnet Mask:"
			+ m_lanSel.GetItemText(nSel, 2)+L"\r\n"
			+L"\t Please confirm your choice and then click OK to continue.";
		SetDlgItemText(IDC_STATIC, str);
		theApp.netMode = nSel;
	}
	*pResult = 0;
}


void LanSelDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (-1 == theApp.netMode) {
		AfxMessageBox(L"You MUST select one network apater.");
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
	int pos = m_lanSel.GetItemCount();
	//m_lanSel.InsertItem(LVIF_TEXT | LVIF_STATE, pos, modeName,
		//(pos % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0);
   // m_lanSel.SetItemText(pos, 0, modeName);
	m_lanSel.InsertItem(pos,modeName);
	m_lanSel.SetItemText(pos, 1, ip);
	m_lanSel.SetItemText(pos, 2, mark);

	return 0;
}


BOOL LanSelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// TODO:  Add extra initialization here
	m_lanSel.InsertColumn(0, L"网络适配器名称", LVCFMT_CENTER, 240, -1);
	m_lanSel.InsertColumn(1, L"IP 地址", LVCFMT_CENTER, 200, -1);
	m_lanSel.InsertColumn(2, L"子网掩码", LVCFMT_CENTER, 200, -1);
	//m_lanSel.InsertColumn(3, L"MARK", LVCFMT_LEFT, 100, -1);
	//DWORD dwStyle = m_lanSel.GetExtendedStyle();

	DWORD dwStyle = m_lanSel.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	//dwStyle |= LVS_EX_GRIDLINES;
	//dwStyle |= LVS_EX_CHECKBOXES;
	m_lanSel.SetExtendedStyle(dwStyle);

	//int pos = 0;
	/*
	m_lanSel.InsertItem(LVIF_TEXT | LVIF_STATE, pos, L"以太网",
		(pos % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0);
	m_lanSel.SetItemText(pos, 0, L"以太网");
	m_lanSel.SetItemText(pos, 1, L"0.0.0.0");
	m_lanSel.SetItemText(pos, 2, L"255.255.255.0");*/

	for (int i = 0; i < AdapterNum; i++) {
	     insertLanmode(szAdapterName[i], szIP[i], szMask[i]);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
