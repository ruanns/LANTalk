#pragma once

// SockMsg command target

#define UDP_PORT 8932
#define DADA_LENGTH 1500

struct UDP_Pack
{
	int nCmd;
	//int dataLen;
	char data[DADA_LENGTH];
};

struct StrInfo
{
	char ip[16];
	char name[16];
	char pc[16];
	char mask[16];
};

struct uInfo
{
	unsigned int ip;
	unsigned int mask;
};
enum
{
	SEND_ON = 0x12f2,
	SEND_MSG = 0x12f3,
	SEND_REPLY = 0x12f4,
};

unsigned int ip2int(CString mask);
CString int2ip(unsigned int imask);

class SockMsg : public CAsyncSocket
{
public:
	SockMsg();
	virtual ~SockMsg();
	//virtual void OnReceive(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


