
// LANTalk.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#define ID_TIMER1 1034

#include "SockMsg.h"
#include "basicClass.h"

#define MAX_USER_NUM 256


// CLANTalkApp:
// See LANTalk.cpp for the implementation of this class
//

class CLANTalkApp : public CWinApp
{
public:
	CLANTalkApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
public:
	//SockMsg m_msg;
	//CString szMark;
	//unsigned int mask;
	//char Name[16], pc_name[16];
	//in_addr * addr;
	StrInfo sInfo;
	uInfo info;
	SockMsg Mymsg;
	EUser user[MAX_USER_NUM];
	int currentUserNum;
	int totalNum;
	int listMap[MAX_USER_NUM];
	int netMode;

	int bPort;

public:
	int InitialNetwork();
	int SayHello();
	int ReplyHello(CString desIP);
	int SendMsg(CString sIP, CString MyMsg);
	virtual int ExitInstance();
	//int SendMessage();
};

extern CLANTalkApp theApp;