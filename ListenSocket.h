#pragma once

// CListenSocket command target

#define MAX_BLOCK_LENGTH 100 * 1024

#define TCP_PORT 12906

enum
{
	SEND_REQUEST = 0x12f8,
	SEND_AGREE = 0x12f9,
	SEND_DATA = 0x12f10,
};


class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	virtual void OnAccept(int nErrorCode);
};


