// ChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LANTalk.h"
#include "ChatDlg.h"
#include "afxdialogex.h"


// CChatDlg dialog

IMPLEMENT_DYNAMIC(CChatDlg, CDialog)

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatDlg::IDD, pParent)
{

}

CChatDlg::~CChatDlg()
{
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_edit);
	DDX_Control(pDX, IDC_LIST_USER, m_user);
	//DDX_Control(pDX, IDC_RICHEDIT23, m_message);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_message);
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatDlg::OnBnClickedButtonSend)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USER, &CChatDlg::OnNMClickListUser)
END_MESSAGE_MAP()


// CChatDlg message handlers


void CChatDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(&rect, 1);
	//UpdateWindow();
	//Invalidate(1);
	//UpdateWindow();

	// TODO: Add your message handler code here
	//Invalidate(0);
	//if (m_edit)
		//m_edit.SetWindowPos(NULL, cx * 2 / 5, cy * 4 / 7, cx * 3 / 5, cy * 3 / 7 - 30, SWP_NOZORDER);
	//CWnd * cWnd = GetDlgItem(IDC_BUTTON_SEND);
	//if (cWnd)
		//cWnd->SetWindowPos(NULL, cx - 70, cy - 30, 70, 30,SWP_NOZORDER);
	//cWnd = GetDlgItem(IDC_STATIC_INPUT);
	//if (cWnd)
		//cWnd->SetWindowPos(NULL, cx * 2 / 5, cy * 4 / 7 - 3, cx * 3 / 5, cy * 3 / 7,SWP_NOZORDER);
	
}


void CChatDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	CRect rect;
	GetClientRect(&rect);
	int cx = rect.Width(), cy = rect.Height();
	if (m_edit)
		m_edit.SetWindowPos(NULL, cx * 2 / 5, cy * 4 / 7, cx * 3 / 5, cy * 3 / 7 - 30, SWP_NOZORDER);
	if (m_message)
		m_message.SetWindowPos(NULL, cx * 2 / 5, 0, cx * 3 / 5, cy * 4 / 7, SWP_NOZORDER);
	CWnd * cWnd = GetDlgItem(IDC_BUTTON_SEND);
	if (cWnd)
		cWnd->SetWindowPos(NULL, cx - 70, cy - 30, 70, 30, SWP_NOZORDER);
	//cWnd = GetDlgItem(IDC_STATIC_CHAT);
	//if (cWnd)
	   // cWnd->SetWindowPos(NULL, cx * 2 / 5, cy * 4 / 7 - 4, cx * 3 / 5, cy * 3 / 7 + 4,SWP_NOZORDER);
	cWnd = GetDlgItem(IDC_LIST_USER);
	if (cWnd)
		cWnd->SetWindowPos(NULL, 0, 0, cx * 2 / 5, cy, SWP_NOZORDER);
	dc.FillSolidRect(&rect, RGB(255, 255, 255));
}

CListCtrl * CChatDlg::GetUserListControl()
{
	return &m_user;
}

int CChatDlg::InitialUserList()
{
	m_user.InsertColumn(0, L"USER NAME", LVCFMT_LEFT, 150, -1);
	m_user.InsertColumn(1, L"HOST NAME", LVCFMT_LEFT, 150, -1);
	m_user.InsertColumn(2, L"IP ADDRESS", LVCFMT_LEFT, 150, -1);
	m_user.InsertColumn(3, L"MASK", LVCFMT_LEFT, 150, -1);
	
	DWORD dwStyle = m_user.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT; 
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_CHECKBOXES;
	m_user.SetExtendedStyle(dwStyle); 
	return 0;
}


BOOL CChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitialUserList();
	m_message.SetReadOnly(1);

	pCurrentUser = NULL;

	theApp.SayHello();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


//int CChatDlg::InitialtToolBar()
//{
//	
//	return 0;
//}


void CChatDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知?理程序代?
	int nSel = m_user.GetSelectedCount() - 1;
	if (nSel < 0)
	{
		AfxMessageBox(L"We haven't find other users until now.");
		return;
	}
	EUser* pUser = &theApp.user[nSel];
	CString userName = pUser->GetName();
	CString input, tmpStr;
	int nLen = GetDlgItemText(IDC_EDIT_INPUT, input);
	if (nLen <= 0)
	{
		tmpStr.LoadStringW(ERROR_EMPUTY_MESSAGE);
		AfxMessageBox(tmpStr);
		return;
	}

	//Send part
	CString showStr;
	CTime time = CTime::GetCurrentTime();
	tmpStr = time.Format(_T("[%Y,%B %d, %A %H:%M:%S ]"));
	EMessage msg = EMessage(tmpStr, input, TRUE, TRUE, FALSE);
	pUser->insertMsg(msg);

	tmpStr.LoadStringW(SEND_MESSAGE_FORMAT);
	showStr.Format(tmpStr, userName, time.Format(_T("[%Y,%B %d, %A %H:%M:%S ]")), input);

	//Save record


	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_SHOW);
	pEdit->SetSel(pEdit->GetWindowTextLength(), -1);
	pEdit->ReplaceSel(showStr);
	SetDlgItemText(IDC_EDIT_INPUT, L"");
}


void CChatDlg::OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知?理程序代?
	int nSel = pNMItemActivate->iItem;
	if (nSel < 0)
	{ 
		return;
	}
	else {
		if (NULL == pCurrentUser)
			pCurrentUser = &theApp.user[nSel];
		SetDlgItemTextW(IDC_EDIT_SHOW, L"");
		CString showStr = pCurrentUser->GetAllMessage();
		m_message.SetWindowText(showStr);

		GetDlgItem(IDC_EDIT_INPUT)->SetFocus();
		CString tmp;
		tmp.Format(L"now selected No.%d\r\n %s", nSel, theApp.user[nSel].GetName() + "\t" + theApp.user[nSel].GetIp());
		AfxMessageBox(tmp);
		return;
	}
	*pResult = 0;
}



