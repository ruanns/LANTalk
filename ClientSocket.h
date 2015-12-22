#pragma once

// CClientSocket command target

#include "ClientSocket.h"
#include "afx.h"

struct tcpData
{
	//int nCmd;
	unsigned int uByte;
	unsigned int uBlock;
	BYTE data[MAX_BLOCK_LENGTH];
};


class CClientSocket : public CSocket
{
	friend CListenSocket;
public:
	CClientSocket();
	virtual ~CClientSocket();
	//virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
protected:
	int nID;
	int nSend;
public:
	virtual void OnReceive(int nErrorCode);
	int OnSendRequest();
	int SendFile();
protected:
	CFile * m_File;
	ULONGLONG uBlock;
	ULONGLONG uReceivedBlock;
	ULONGLONG uLength;
public:
	int OnSendAgree();
	int OnSendInfo();
	int OnSendData();
	int OnSendBegin();
	int OnSendEnsure();
};


