// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "LANTalk.h"
#include "ClientSocket.h"
#include "LANTalkDlg.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket member functions




void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CSocket::OnClose(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//tcpData tData;
	int nCmd;
	if (Receive(&(nCmd), sizeof(int)) <= 0)
		return;
	switch (nCmd)
	{
	case SEND_REQUEST:
		OnSendRequest();
	case SEND_AGREE:
		OnSendAgree();
	default:
	

		break;
	}
	CSocket::OnReceive(nErrorCode);
}


int CClientSocket::OnSendRequest()
{
	tcpData tData;
	UINT port;
	CString IP;
	GetPeerName(IP, port);
	if (Receive(&tData, sizeof(tcpData) )<= 0)
		return -1;
	int * lengthType = (int *)&(tData.data);
	double * length = (double *)(&(tData.data) + 4);
	CString FileLen;
	if (*lengthType == 1)
		FileLen.Format(L"%d %s", int(*length), L"kB");
	else if (*lengthType == 2)
		FileLen.Format(L"%d %s", int(*length), L"MB");
	else if (*lengthType == 3)
		FileLen.Format(L"4.2f %s", length, L"GB");
	CLANTalkDlg * dlg = (CLANTalkDlg *)AfxGetMainWnd();
	if (dlg->AcceptFile(CString(tData.data + 12), FileLen, IP, nID, m_File) == 0)
	{
		Close();
		delete this;
		return 1;
	}
	
	return 0;
}


int CClientSocket::SendFile()
{
	return 0;
}


int CClientSocket::OnSendAgree()
{
	
	return 0;
}
