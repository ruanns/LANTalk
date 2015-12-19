
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

	currentUserNum = -1;
	CLANTalkDlg dlg;
	m_pMainWnd = &dlg;
	InitialNetwork();
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



int CLANTalkApp::InitialNetwork()
{
	if (!Mymsg.Create(UDP_PORT, SOCK_DGRAM))
	{
		AfxMessageBox(L"Create Port Failed");
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
	hostent * host = gethostbyname(sInfo.pc);
	in_addr * addr = (in_addr *)host->h_addr_list[0];

	CString szMark;

	wchar_t * wMask;

	

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



	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {

		pAdapter = pAdapterInfo;

		while (pAdapter)

		{


			szMark.Format(_T("%s"), CA2W(pAdapter->IpAddressList.IpMask.String));

			pAdapter = pAdapter->Next;

		}

	}

	wMask = szMark.GetBuffer(szMark.GetLength());

	for (int i = 0; i < szMark.GetLength(); i++)
		sInfo.mask[i] = char(UINT16(wMask[i]));

	

	CString csIp;
	info.mask = ip2int(szMark);
	info.ip = addr->S_un.S_addr;
	csIp = int2ip(info.ip);

	wchar_t * wIp = csIp.GetBuffer(csIp.GetLength());

	for (int i = 0; i < csIp.GetLength(); i++)
		sInfo.ip[i] = char(UINT16(wIp[i]));

	

	
	//info.ip = ip2int(csIp);
	//AfxMessageBox(str);
	return 0;
}

