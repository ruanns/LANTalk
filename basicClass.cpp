#include "stdafx.h"
#include "basicClass.h"

//using namespace std;



//EUser

EUser::EUser(CString _name, CString _hostname, CString _ip, CString _mark/*, UINT _group = 0*/)
{
	userName = _name;
	hostName = _hostname;
	ipAddress = _ip;
	Mark = _mark;
	msgNum = 0;
	pMsg = NULL;
	endMsg = NULL;
}

void EUser::EditName(CString _name)
{
	userName = _name;
}

CString EUser::GetHostName()
{
	return CString(hostName);
}

CString EUser::GetName()
{
	return CString(userName);
}

CString EUser::GetIp()
{
	return ipAddress;
}

CString EUser::GetMark()
{
	return Mark;
}
EMessage * EUser::GetPmsg()
{
	return pMsg;
}

UINT EUser::GetMsgNum()
{
	return msgNum;
}

CString EUser::GetAllMessage()
{
	CString allMsg;
	if (0 == msgNum | NULL == pMsg)
	{
		allMsg = L"";
	}
	else {
		allMsg = L"";
		EMessage* p = pMsg;
		EMessage* tmpMsg = NULL;
		EMessage* next = NULL;
		CString tmpFor,tmpStr;
		for (UINT i = 0; i <= msgNum && p != NULL; i++)
		{
			if (TRUE == p->GetSrMark()) {
				tmpFor.LoadStringW(SEND_MESSAGE_FORMAT);
			}
			else {
				tmpFor.LoadStringW(RECEIVE_MESSAGE_FORMAT);
			}
			tmpStr.Format(tmpFor, userName, p->GetTime(), p->GetContent());
			allMsg = allMsg + tmpStr;
			tmpMsg = p;
			next = tmpMsg->GetNextMsg();
		}
	}

	return CString(allMsg);
}

void EUser::insertMsg(EMessage * _pMsg)
{
	if (0 == msgNum)
	{
		pMsg = _pMsg;
	}
	endMsg->SetNextMsg(_pMsg);
	msgNum++;
}

EMessage::EMessage(CString _t, CString _m, bool _sr, bool _read, bool _burn)
{
	time = _t;
	content = _m;
	nextMsg = NULL;
	srMark = _sr;
	readMark = _read;
	burnMark = _burn;
}

CString EMessage::GetTime()
{
	return CString(time);
}

CString EMessage::GetContent()
{
	return CString(content);
}

EMessage * EMessage::GetNextMsg()
{
	return nextMsg;
}

BOOL EMessage::GetSrMark()
{
	return srMark;
}

BOOL EMessage::GetReadMark()
{
	return readMark;
}

BOOL EMessage::GetBurnMark()
{
	return burnMark;
}

void EMessage::SetNextMsg(EMessage * _pMsg)
{
	nextMsg = _pMsg;
}

void EMessage::ChangeRmk()
{
	readMark = TRUE;
}

EMessage::~EMessage()
{
}



