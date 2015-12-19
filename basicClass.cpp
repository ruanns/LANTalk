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
EMessage::EMessage(CString cont = L"", bool bmk =  FALSE, bool srmk = TRUE, bool rmk = FALSE)
{
	length = cont.GetLength();
	content = cont;
	burnMark = bmk;
	srMark = srmk;
	readMark = rmk;
}

void EMessage::ChangeRmk()
{
	readMark = TRUE;
}

EMessage::~EMessage()
{
}



