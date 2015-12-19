// SockMsg.cpp : implementation file
//

#include "stdafx.h"
#include "LANTalk.h"
#include "SockMsg.h"
#include "LANTalkDlg.h"


// SockMsg

SockMsg::SockMsg()
{
}

SockMsg::~SockMsg()
{
}


unsigned int ip2int(CString mask)
{
	wchar_t * m1;
	m1 = mask.GetBuffer(mask.GetLength());
	unsigned int imask = 0;
	int len = mask.GetLength();
	int x[4][3];
	for (int m = 0; m < 4; m++)
	{
		for (int n = 0; n < 3; n++)
			x[m][n] = 0;
	}
	int mul[3] = { 1, 10, 100 };
	int i = 0, j = 0;
	for (int k = 0; k < len; k++)
	{
		if (m1[k] == L'.')
		{
			j = 0;
			i = i + 1;
		}
		else
		{
			for (int s = j; s >= 0; s--)
				x[i][s + 1] = x[i][s];
			x[i][0] = int(m1[k] - 48);
			j++;

		}
	}
	for (int m = 3; m >= 0; m--)
	{
		imask = imask << 8;
		int temp = 0;
		for (int n = 0; n < 3; n++)
			temp = temp + x[m][n] * mul[n];
		imask = imask + temp;

	}
	return imask;
}

CString int2ip(unsigned int imask)
{
	char sMask[16];
	memset(sMask, 0, 16);
	unsigned int b[4];
	b[0] = (imask >> 24) & 0x000000ff;
	b[1] = (imask >> 16) & 0x000000ff;
	b[2] = (imask >> 8) & 0x000000ff;
	b[3] = (imask) & 0x000000ff;

	int i = 0, k = 0;
	for (k = 0; k < 16; k++)
	{
		if (i > 3)
			break;
		sMask[k] = char(b[i] % 10 + 48);
		b[i] = b[i] / 10;
		if (b[i] == 0)
		{
			sMask[++k] = '.';
			i++;
		}
	}
	k--;
	sMask[k] = 0;

	char tmp;
	for (int j = 0; j <= (k - 1) / 2; j++)
	{
		tmp = sMask[j];
		sMask[j] = sMask[k - 1 - j];
		sMask[k - 1 - j] = tmp;
	}
	
	return CString(sMask);
}




// SockMsg member functions





void SockMsg::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	CLANTalkDlg * dlg = (CLANTalkDlg *)AfxGetMainWnd();
	UDP_Pack pack1;
	memset(&pack1, 0, sizeof(UDP_Pack));
	CString  sIP;
	UINT port = UDP_PORT;

	while (ReceiveFrom(&pack1, sizeof(pack1),sIP,port))
	{
		if (pack1.nCmd = SEND_ON)
		if (pack1.nCmd == SEND_ON)
		{
			StrInfo UserInfo;
			memcpy(&UserInfo, pack1.data, sizeof(UserInfo));
			CString sName(UserInfo.name);
			CString sPCName(UserInfo.pc);
			CString sMask(UserInfo.mask);
			CString sIP(UserInfo.ip);
			dlg->InsertUser(sName, sPCName, sIP, sMask);
			if (sIP != CString(theApp.sInfo.ip))
				theApp.ReplyHello(sIP);
			break;
		}
		if (pack1.nCmd = SEND_REPLY)
		else if (pack1.nCmd == SEND_REPLY)
		{
			StrInfo UserInfo;
			memcpy(&UserInfo, pack1.data, sizeof(UserInfo));
			CString sName(UserInfo.name);
			CString sPCName(UserInfo.pc);
			CString sMask(UserInfo.mask);
			CString sIP(UserInfo.ip);
			dlg->InsertUser(sName, sPCName, sIP, sMask);
			break;
		}
		if (pack1.nCmd == SEND_MSG)
		else if (pack1.nCmd == SEND_MSG)
		{
			wchar_t * wMsg = (wchar_t *)pack1.data;
			//UINT16 MsgLen = (UINT16)wMsg[0];
			CString csMsg(wMsg + 1);
			//dlg->InserMessage(sIP,csMsg);
		}
	}

	

	CAsyncSocket::OnReceive(nErrorCode);
}

