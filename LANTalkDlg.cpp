
// LANTalkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LANTalk.h"
#include "LANTalkDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLANTalkDlg dialog



CLANTalkDlg::CLANTalkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLANTalkDlg::IDD, pParent)
	//, SelectedAdapter(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLANTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLANTalkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CLANTalkDlg message handlers

BOOL CLANTalkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	// TODO: Add extra initialization here
	//-----------------Receive file dialog (For debug use)-----------
	//m_recvFile.Create(IDD_RECEIVE_FILE);
	//m_recvFile.ShowWindow(SW_SHOW);
	//CString info, fmt;
	//fmt.LoadStringW(RECV_FILE_INFO);
	//info.Format(fmt, L"0.0.0.0", L"123.txt", L"3.87 Mb");
	//info += L" Do you want to accept it?";
	//m_recvFile.SetDlgItemTextW(IDC_FILE_INFO, info);
	//INT_PTR result = m_recvFile.DoModal();// bug!
	//-----------------LAN network setting dialog--------------------
	
	//m_lan.Create(IDD_LAN_SELECT);
	//m_lan.InitialLanSelList();
	//m_lan.ShowWindow(SW_SHOW);
	
	//m_lan.DoModal();// Bug!

	//theApp.bPort = InitialNetwork();

	AfxInitRichEdit2();
	m_chat.Create(IDD_CHAT);
	m_chat.ShowWindow(SW_SHOWNORMAL);
	SetTimer(ID_TIMER1, 10000, NULL);

	
	//lanSel.Create(IDD_LAN_SELECT);
	//lanSel.InitialLanSelList();
	//for (int i = 0; i < iNum; i++) {
		//	lanSel.insertLanmode(szNameAdapter[i], szIP[i], szMask[i]);
	//}
	////lanSel.ShowWindow(SW_SHOW);
   //LanSelDlg lanSel;
   //lanSel.DoModal();
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLANTalkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLANTalkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		int cx = rect.Width(), cy = rect.Height();
		//dc.FillSolidRect(rect, RGB(255, 192, 203));
		CWnd * talkWnd = (CWnd *)&m_chat;
		if (talkWnd)
			talkWnd->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
		dc.FillSolidRect(rect, RGB(51, 161, 201));
		
		CDialogEx::OnPaint();
		
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLANTalkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLANTalkDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	Invalidate(1);
	UpdateWindow();

	// TODO: Add your message handler code here
	//CPaintDC dc(this);
	//CRect rect;
	//GetClientRect(&rect);
	//CWnd * talkWnd = (CWnd *)&m_chat;
	
	//talkWnd->SetWindowPos(NULL, rect.left, rect.top + 80, rect.Width(), rect.Height() - 80, SWP_NOZORDER);
	//dc.FillSolidRect(rect, RGB(255, 192, 203));
	
}

CChatDlg * CLANTalkDlg::GetChatDlg()
{
	return &m_chat;
}

void CLANTalkDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox(L"Hello");
	//unsigned int imask = theApp.mask;
	//unsigned int myip = (theApp.addr)->S_un.S_addr;
	//unsigned int broad_ip = myip | (~imask);
	//UDP_Pack pack;
	//memset(&pack, 0, sizeof(UDP_Pack));
	//pack.nCmd = SEND_ON;
	//unsigned int broad_ip = theApp.info.ip | (~theApp.info.mask);
	//CString BIP = int2ip(broad_ip);
	//BIP = L"59.66.176.121";
	//memcpy(pack.data, &(theApp.sInfo), sizeof(StrInfo));
	//BOOL bBroadcast = TRUE;
	//theApp.Mymsg.SetSockOpt(SO_BROADCAST, (char *)&bBroadcast, sizeof(BOOL));
	//sockaddr_in local;
	//int len = sizeof(local);
	//memset(&local, 0, len);
	//local.sin_family = AF_INET;
	//local.sin_port = htons(UDP_PORT);//htons(dwPort);
	//local.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	//if (theApp.Mymsg.SendTo(&pack, sizeof(StrInfo) + sizeof(int), (const SOCKADDR*)&local, len) == SOCKET_ERROR)
	//{
		//theApp.Mymsg.GetLastError();
	//}
	//theApp.Mymsg.SendTo(&pack, sizeof(StrInfo) + sizeof(int), UDP_PORT, BIP);
	//for (int i = 0; i < 16; i++)
	//{
		//pack.data[i] = theApp.Name[i];
		//pack.data[i + 16] = theApp.pc_name[i];
	//}

	CDialogEx::OnTimer(nIDEvent);
}

int CLANTalkDlg::SendMsg(CString sIP, CString MyMsg)
{
	UDP_Pack pack;
	memset(&pack, 0, sizeof(UDP_Pack));
	pack.nCmd = SEND_MSG;

	wchar_t * wMsg = MyMsg.GetBuffer(MyMsg.GetLength());
	UINT16 len = min(DADA_LENGTH - 2, MyMsg.GetLength() * 2);

	memcpy(pack.data + 2, wMsg, len);
	pack.data[1] = UINT8(len && 0x00ff);
	pack.data[0] = UINT8((len >> 8) && 0x00ff);


	theApp.Mymsg.SendTo(&pack, sizeof(int) + len + 2, UDP_PORT, sIP);

	//unsigned int broad_ip = theApp.info.ip | (~theApp.info.mask);
	//CString BIP = int2ip(broad_ip);
	//memcpy(pack.data, &(theApp.sInfo), sizeof(StrInfo));
	//theApp.Mymsg.SendTo(&pack, sizeof(StrInfo) + sizeof(int), UDP_PORT, sIP);
	return 0;
}

void CLANTalkDlg::InsertUser(CString UserName, CString HostName, CString IP, CString Mark)
{
	if (L"" == UserName || L"" == HostName || L"" == IP || L"" == Mark) {
		AfxMessageBox(L"Error happened when inserting a user into the user-list.");
		return;
	}
	int pos = -1;
	if (theApp.totalNum >= 0){
		int i = 0;
		do{
			if (IP == theApp.user[i].GetIp()){
				pos = i;
				break;
			}
			i++;
		} while (i <= theApp.totalNum);
	}
	//this is a new user
	if (-1 == pos) {
		theApp.currentUserNum++;
		theApp.totalNum++;
		int n = theApp.currentUserNum;
		theApp.listMap[n] = theApp.totalNum;
		theApp.user[theApp.totalNum] = EUser(UserName, HostName, IP, Mark);
	}
	else {
		if (theApp.currentUserNum >= 0) {
			int i = 0;
			BOOL isInList = FALSE;//is in the  user-list showed
			do {
				if (IP == theApp.user[theApp.listMap[i]].GetIp()) {
					isInList = TRUE;
					break;
				}
				i++;
			} while (i <= theApp.currentUserNum);
			if (isInList) {
				return;
			}
		}
		theApp.currentUserNum++;
		int n = theApp.currentUserNum;
		theApp.listMap[n] = pos;
	}		
	
	//CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_USER);
	CListCtrl *pList;
	pList = m_chat.GetUserListControl();
	pos = theApp.currentUserNum;//
	//int nColumnCount = pList->GetHeaderCtrl()->GetItemCount();

	//pList->InsertItem(LVIF_TEXT | LVIF_STATE, pos, UserName,
		//(pos % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0);
	pList->InsertItem(pos, UserName);
	//pList->SetItemText(pos, 0, UserName);
	pList->SetItemText(pos, 1, HostName);
	pList->SetItemText(pos, 2, IP);
	pList->SetItemText(pos, 3, Mark);
	pList = NULL;
}

int CLANTalkDlg::deleteUser(CString ip)
{
	if (L"" != ip && theApp.currentUserNum >= 0) {
		int pos = -1;
		for (int i = 0; i <= theApp.currentUserNum; i++) {
			if(ip == theApp.user[theApp.listMap[i]].GetIp()){
				for (int j = i; j <= theApp.currentUserNum; j++) {
					if (MAX_USER_NUM - 1 == j) {
						theApp.listMap[j] = -1;
					}
					else {
						theApp.listMap[j] = theApp.listMap[j + 1];
					}					
				}
				theApp.currentUserNum--;
			}
		}
	}
	return 0;
}

FileInfo CLANTalkDlg::AcceptFile(CString FileName, CString FileLength, CString FrmIP)
{

	CString info, fmt;
	fmt.LoadStringW(RECV_FILE_INFO);
	info.Format(fmt, FrmIP, FileName, FileLength);
	CRecvFileDlg recvFile(FileName, info);
	//recvFile.SetDlgItemTextW(IDC_FILE_INFO,info);
	INT_PTR result = recvFile.DoModal();

	FileInfo fInfo;
	if (IDOK == result) {
		//CFile* openFile = new CFile();
		CString fullPath = recvFile.saveFolderPath + L"\\" + FileName;
		EFile file(fullPath, FileName, 0.0, FALSE);
		theApp.fileList.InsertToList(file);
		//insert to message record

		//parameter structure to return 
		fInfo.ID = file.GetId();
		fInfo.file = fullPath;
		fInfo.iAccept = 1;
		//if (openFile->Open(fullPath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary)) {
		//	}
	}
	else {
		fInfo.ID = -1;
		fInfo.file = L"";
		fInfo.iAccept = 0;
	}
	//recvFile.CloseWindow();//if necessary ?

	return FileInfo(fInfo);
}