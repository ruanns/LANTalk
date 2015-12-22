#pragma once

// CListenSocket command target

#define MAX_BLOCK_LENGTH 100 * 1024

#define TCP_PORT 12906

enum
{
	SEND_REQUEST = 0x12f8,
	SEND_AGREE = 0x12f9,
	SEND_DATA = 0x12fa,
	SEND_INFO = 0x12fb,
	SEND_BEGIN = 0x12fc,
	SEDN_ENSURE = 0x12fd,
};


class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	virtual void OnAccept(int nErrorCode);
};


