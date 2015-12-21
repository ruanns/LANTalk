// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "LANTalk.h"
#include "ListenSocket.h"
#include "ClientSocket.h"



// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket member functions


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	CClientSocket * pSock = new CClientSocket();
	if (!Accept(*pSock))
		delete pSock;
	pSock->nSend = 0;
	//pSock->nID = theApp.NewID();
	CSocket::OnAccept(nErrorCode);
}
