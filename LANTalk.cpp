
// LANTalk.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LANTalk.h"
#include "LANTalkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "IPHLPAPI.lib")


// CLANTalkApp

BEGIN_MESSAGE_MAP(CLANTalkApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLANTalkApp construction

CLANTalkApp::CLANTalkApp()
	: iNetUseful(0)
	//, iNetUseful(0)
	, SelectedAdapter(0)
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CLANTalkApp object

CLANTalkApp theApp;


// CLANTalkApp initialization

BOOL CLANTalkApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	

	AfxEnableControlContainer();

	

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	netMode = -1;
	currentUserNum = -1;
	totalNum = -1;
	for (int i = 0; i < MAX_USER_NUM; i++)
		listMap[i] = -1;
	CLANTalkDlg dlg;
	m_pMainWnd = &dlg;

	//InitialNetwork();
	
	//m_pMainWnd->SetTimer(ID_TIMER1, 2000, NULL);
	INT_PTR nResponse = dlg.DoModal();
	
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
		
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}




	


int CLANTalkApp::SayHello()
{
	if (!iNetUseful)
		return -1;
	UDP_Pack pack;
	memset(&pack, 0, sizeof(UDP_Pack));
	pack.nCmd = SEND_ON;
	//pack.dataLen = sizeof(StrInfo);
	unsigned int //broad_ip = theApp.info.ip | (~theApp.info.mask),
		begin_ip = info.ip & (info.mask),
		mask = info.mask;
	//CString BIP = int2ip(broad_ip);
	//BIP = L"59.66.176.121";
	int mask_len = 0;
	unsigned int k = 1 << 31;
	while ((k & mask) == 0)
	{
		k = k >> 1;
		mask_len++;
	}
	
	
	
	memcpy(pack.data, &(sInfo), sizeof(StrInfo));
	
	//BOOL bBroadcast = TRUE;
	//theApp.Mymsg.SetSockOpt(SO_BROADCAST, (char *)&bBroadcast, sizeof(BOOL));
	//sockaddr_in local;
	//int len = sizeof(local);
	//memset(&local, 0, len);
	//local.sin_family = AF_INET;
	//local.sin_port = htons(UDP_PORT);//htons(dwPort);
	//unsigned int i = 89;
	unsigned int des_addr = begin_ip;
	for (unsigned int i = 1;i < (unsigned int)((1 << (mask_len)) - 1);i++)
	{
		//des_addr += 1;
		des_addr += (1 << (32 - mask_len));
		//local.sin_addr.s_addr = htonl(des_addr);
		CString p = int2ip(des_addr);
		//if (theApp.Mymsg.SendTo(&pack, sizeof(StrInfo) + sizeof(int), (const SOCKADDR*)&local, len) == SOCKET_ERROR)
		if (Mymsg.SendTo(&pack, sizeof(StrInfo) + sizeof(int), UDP_PORT, int2ip(des_addr)) == SOCKET_ERROR)
		{
			Mymsg.GetLastError();
		}
	}
	
	
	//theApp.Mymsg.SendTo(&pack, sizeof(StrInfo) + sizeof(int), UDP_PORT, BIP);
	return 0;
}


int CLANTalkApp::ReplyHello(CString desIP)
{
	
	UDP_Pack pack;
	memset(&pack, 0, sizeof(UDP_Pack));
	pack.nCmd = SEND_REPLY;
	//pack.dataLen = sizeof(StrInfo);
	memcpy(pack.data, &(sInfo), sizeof(StrInfo));

	
	if (Mymsg.SendTo(&pack, sizeof(StrInfo) + sizeof(int), UDP_PORT, desIP) == SOCKET_ERROR)
	{
		Mymsg.GetLastError();
	}
	return 0;
}


int CLANTalkApp::InitialNetwork()
{
	if (!Mymsg.Create(UDP_PORT, SOCK_DGRAM))
	{
		AfxMessageBox(L"Create Port Failed");
		Mymsg.Close();
		return 1;
	}

	//char info[128];
	//wchar_t UserName[32];
	memset(&sInfo, 0, sizeof(StrInfo));
	DWORD UserNameLen = 16;
	//GetComputerName(PCName, & PCNameLen);
	GetUserNameA(sInfo.name, &UserNameLen);
	//CString str(UserName);
	//AfxMessageBox(str);
	gethostname(sInfo.pc, 16);
	//hostent * host = gethostbyname(sInfo.pc);
	//in_addr * addr = (in_addr *)host->h_addr_list[0];

	//CString szMark;

	//wchar_t * wMask;

	CString * szMask = NULL, *szIP = NULL, *szNameAdapter = NULL;



	PIP_ADAPTER_INFO pAdapterInfo;

	PIP_ADAPTER_INFO pAdapter = NULL;

	DWORD dwRetVal = 0;

	pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));

	ULONG ulOutBufLen;


	ulOutBufLen = sizeof(IP_ADAPTER_INFO);




	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)

	{

		free(pAdapterInfo);

		pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);

	}


	int iAdapter = 0;

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {

		pAdapter = pAdapterInfo;
		PIP_ADAPTER_INFO pAdapter1 = pAdapter;

		while (pAdapter1)

		{


			//szMark.Format(_T("%s"), CA2W(pAdapter1->IpAddressList.IpMask.String));
			iAdapter++;

			pAdapter1 = pAdapter1->Next;

		}

	}

	int iUsefulAdapter = 0;
	if (iAdapter)
	{
		//char ipTmp[16];
		szMask = new CString[iAdapter]();
		szIP = new CString[iAdapter]();
		szNameAdapter = new CString[iAdapter]();
		while (pAdapter)
		{
			//szMark.Format(_T("%s"), CA2W(pAdapter1->IpAddressList.IpMask.String));
			//iAdapter++;
			//memcpy(&ipTmp, pAdapter->IpAddressList.IpAddress.String, 16);
			if (CString(CA2W(pAdapter->IpAddressList.IpMask.String)) != L"0.0.0.0")
			{
				szMask[iUsefulAdapter].Format(_T("%s"), CA2W(pAdapter->IpAddressList.IpMask.String));
				szIP[iUsefulAdapter].Format(_T("%s"), CA2W(pAdapter->IpAddressList.IpAddress.String));
				szNameAdapter[iUsefulAdapter].Format(_T("%s"), CA2W(pAdapter->Description));
				iUsefulAdapter++;
			}

			pAdapter = pAdapter->Next;
		}
	}

	if (iUsefulAdapter == 0)
	{
		//iNetUseful = 0;
		return -1;
	}

	iNetUseful = 1;
	SelectAdapter(szNameAdapter, szIP, szMask, iUsefulAdapter);

	int iSelect = netMode;

	//wMask = szMask[iSelect].GetBuffer(szMask[iSelect].GetLength());

	//for (int i = 0; i < szMark.GetLength(); i++)
	//sInfo.mask[i] = char(UINT16(wMask[i]));



	CString csIp;
	
	info.mask = ip2int(szMask[iSelect]);
	info.ip = ip2int(szIP[iSelect]);
	//info.ip = addr->S_un.S_addr;
	//csIp = int2ip(info.ip);

	wchar_t * wIp = szIP[iSelect].GetBuffer(szIP[iSelect].GetLength());

	for (int i = 0; i < szIP[iSelect].GetLength(); i++)
		sInfo.ip[i] = char(UINT16(wIp[i]));

	wchar_t * wMask = szMask[iSelect].GetBuffer(szMask[iSelect].GetLength());

	for (int i = 0; i < szMask[iSelect].GetLength(); i++)
		sInfo.mask[i] = char(UINT16(wMask[i]));




	//info.ip = ip2int(csIp);
	//AfxMessageBox(str);
	
	return 0;
}





int CLANTalkApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	Mymsg.Close();
	m_listen.Close();
	EMessage *p = NULL;
	EMessage* tmp = NULL;
	CString msgRecd;
	CFile file;
	BOOL flag = TRUE;
	msgRecd.LoadStringW(RECORD_FILE_NAME);
	if (!file.Open(msgRecd, CFile::modeWrite
		| CFile::typeBinary) )
	{
		AfxMessageBox(L"Error happens when create the record file.");
		flag = FALSE;
	}
		
	for (int i = 0; L"0.0.0.0" != user[i].GetIp() && flag; i++)
	{
		//save message record
		msgRecd = L"";
		msgRecd.Format(L"-----User Name:%s  Host Name:%s  IP:%s  Mark:%s-----",
			user[i].GetName(),user[i].GetHostName(),user[i].
			GetIp(),user[i].GetMask());
		msgRecd = msgRecd + user[i].GetAllMessage();
		wchar_t *tmpChar = msgRecd.GetBuffer(msgRecd.GetLength());
		file.SeekToEnd();
		//file.Write(msgRecd, msgRecd.GetLength()*2);
		file.Write(tmpChar, msgRecd.GetLength() * 2);
		//delete msg
		p = user[i].GetPmsg();
		while (p != NULL)
		{
			tmp = p->GetNextMsg();
			delete p;
			p = tmp;
		}
	}
	if (flag)
		file.Close();

	return CWinApp::ExitInstance();
}

int CLANTalkApp::SendMsg(CString sIP, CString MyMsg)
{
	UDP_Pack pack;
	memset(&pack, 0, sizeof(UDP_Pack));
	pack.nCmd = SEND_MSG;

	wchar_t * wMsg = MyMsg.GetBuffer(MyMsg.GetLength());
	UINT16 len = min(DADA_LENGTH - 2, MyMsg.GetLength() * 2);

	memcpy(pack.data, wMsg, len);
	//pack.dataLen = len;
	//pack.data[1] = UINT8(len && 0x00ff);
	//pack.data[0] = UINT8((len >> 8) && 0x00ff);


	Mymsg.SendTo(&pack, sizeof(int) + len, UDP_PORT, sIP);

	//unsigned int broad_ip = theApp.info.ip | (~theApp.info.mask);
	//CString BIP = int2ip(broad_ip);
	//memcpy(pack.data, &(theApp.sInfo), sizeof(StrInfo));
	//theApp.Mymsg.SendTo(&pack, sizeof(StrInfo) + sizeof(int), UDP_PORT, sIP);
	return 0;
}




int CLANTalkApp::CreateListenSocket()
{
	if (m_listen.Create(TCP_PORT))
		m_listen.Listen();
	return 0;
}


int CLANTalkApp::GetUseFulID()
{
	return 0;
}


int CLANTalkApp::NewID()
{
	return 0;
}

void CLANTalkApp::SaveMsgRecd()
{
	EMessage *p = NULL;
	EMessage* tmp = NULL;
	CString msgRecd;
	CFile file;
	BOOL flag = TRUE;
	msgRecd.LoadStringW(RECORD_FILE_NAME);
	if (!file.Open(msgRecd, CFile::modeWrite
		| CFile::typeBinary))
	{
		AfxMessageBox(L"Error happens when create the record file.");
		flag = FALSE;
	}

	for (int i = 0; L"0.0.0.0" != user[i].GetIp() && flag; i++)
	{
		//save message record
		msgRecd = L"";
		msgRecd.Format(L"-----User Name:%s  Host Name:%s  IP:%s  Mark:%s-----",
			user[i].GetName(), user[i].GetHostName(), user[i].
			GetIp(), user[i].GetMask());
		msgRecd = msgRecd + user[i].GetAllMessage();
		wchar_t *tmpChar = msgRecd.GetBuffer(msgRecd.GetLength());
		file.SeekToEnd();
		//file.Write(msgRecd, msgRecd.GetLength()*2);
		file.Write(tmpChar, msgRecd.GetLength() * 2);
		//delete msg
		p = user[i].GetPmsg();
		while (p != NULL)
		{
			tmp = p->GetNextMsg();
			delete p;
			p = tmp;
		}
	}
	if (flag)
		file.Close();
}

int CLANTalkApp::SelectAdapter(CString * szNameAdapter, CString * szIP, CString * szMask, int iNum)
{
	LanSelDlg lanSel(NULL, szIP, szNameAdapter, szMask, iNum);
	//lanSel.Create(IDD_LAN_SELECT);
	//lanSel.InitialLanSelList();
	//for (int i = 0; i < iNum; i++) {
	   // lanSel.insertLanmode(szNameAdapter[i], szIP[i], szMask[i]);
	//}
	//lanSel.ShowWindow(SW_SHOW);
	lanSel.DoModal();

	return netMode;
}
