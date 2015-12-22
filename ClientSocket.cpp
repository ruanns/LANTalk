// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "LANTalk.h"
#include "ClientSocket.h"
#include "LANTalkDlg.h"


// CClientSocket

CClientSocket::CClientSocket()
{
	uReceivedBlock = 0;
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
	case SEND_INFO:
		OnSendInfo();
	case SEND_DATA:
		OnSendData();
	case SEND_BEGIN:
		OnSendBegin();
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
	memset(&tData, 0, sizeof(tData));
	if (Receive(&tData, sizeof(tData)) <= 0)
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
	FileInfo Finfo = dlg->AcceptFile(CString((wchar_t *)(tData.data + 12)), FileLen, IP);
	//tcpData tData1;
	int iAnswer;
	int nCmd = SEND_AGREE;

	Send(&nCmd, sizeof(nCmd));
	if (Finfo.iAccept == 0)
	{
		
		iAnswer = 1;
		Send(&iAnswer, sizeof(unsigned int));
		//tData1.uByte = 1;
		//Send(& (tData1.uByte), sizeof(unsigned int));
		//Close();
		//delete this;
		return 1;
	}

	m_File = Finfo.file;
	nID = Finfo.ID;

	iAnswer = 2;
	Send(&iAnswer, sizeof(unsigned int));

	//tData1.uByte = 2;
	//Send(&(tData1.uByte), sizeof(unsigned int));
	
	return 0;
}


int CClientSocket::SendFile()
{
	//ULONGLONG length = m_File->GetLength();
	unsigned int BufferSize = MAX_BLOCK_LENGTH;
	ULONGLONG rBuffer = uLength % BufferSize;
	tcpData tData;
	int nCmd = SEND_DATA;
	Send(&nCmd, sizeof(int));
	
	for (ULONGLONG i = 0; i < uBlock; i++)
	{
		if (i != uBlock - 1)
		{
			tData.uByte = BufferSize;
			tData.uBlock = i;
			m_File->Read(tData.data, BufferSize);
			Send(&tData, sizeof(tData));		
		}
		else
		{
			tData.uByte = rBuffer;
			tData.uBlock = i;
			m_File->Read(tData.data, rBuffer);
			Send(&tData, rBuffer + 2 * sizeof(unsigned int));
		}
		
	}

	//m_File->Close();
	//delete m_File;
	return 0;
}


int CClientSocket::OnSendAgree()
{
	unsigned int iAnswer;
	Receive(&iAnswer, sizeof(iAnswer));
	if (iAnswer == 1)
	{
		Close();
		delete this;
		//return iAnswer;
	}
	else if (iAnswer == 2)
	{
		//ULONGLONG length = m_File->GetLength();
		uLength = m_File->GetLength();
		unsigned int BufferSize = MAX_BLOCK_LENGTH;
		ULONGLONG nBuffer = uLength / BufferSize + 1;
		uBlock = nBuffer;
		//int nCmd = SEND_INFO;
		int nCmd = SEND_INFO;
		Send(&nCmd, sizeof(int));
		Send(&nBuffer, sizeof(uLength));

	}
	return iAnswer;
}


int CClientSocket::OnSendInfo()
{
	//reserve space
	Receive(&uLength, sizeof(uLength));
	//uReceivedBlock++;
	int nCmd = SEND_BEGIN;
	int buffer_size = MAX_BLOCK_LENGTH;
	uBlock = uLength / buffer_size;
	Send(&nCmd, sizeof(nCmd));
	int Begin = 1;
	Send(&Begin, sizeof(int));
	return 0;
}


int CClientSocket::OnSendData()
{
	tcpData tData;
	int buffer_size = MAX_BLOCK_LENGTH;
	Receive(&tData, sizeof(tData));
	uReceivedBlock++;
	m_File->Seek(tData.uBlock * buffer_size, CFile::begin);
	m_File->Write(tData.data, tData.uByte);
	if (uReceivedBlock == uBlock)
	{
		//if delete?
		m_File->Close();
		//Close();
		//delete this;
		//return 1;
	}
	
	//m_File->Seek();
	return 0;
}


int CClientSocket::OnSendBegin()
{
	int iBegin;
	Receive(&iBegin, sizeof(int));
	if (iBegin == 1)
		SendFile();

	return 0;
}


int CClientSocket::OnSendEnsure()
{
	int iSure;
	Receive(&iSure, sizeof(iSure));
	if (iSure == 1)
		uReceivedBlock++;
	if (uReceivedBlock == uBlock)
	{
		Close();
		delete this;
		return 1;
	}
	return 0;
}
