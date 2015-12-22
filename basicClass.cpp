#include "stdafx.h"
#include "basicClass.h"

//EUser

EUser::EUser(CString _name, CString _hostname, CString _ip, CString _mark)
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
	if (0 == msgNum || NULL == pMsg)
	{
		allMsg = L"";
	}
	else {
		allMsg = L"";
		EMessage* p = pMsg;
		//EMessage* tmpMsg = NULL;
		EMessage* next = NULL;
		CString tmpFor, tmpStr;
		for (UINT i = 1; i <= msgNum && p != NULL; i++)
		{
			if (TRUE == p->GetSrMark()) {
				tmpFor.LoadStringW(SEND_MESSAGE_FORMAT);
			}
			else {
				tmpFor.LoadStringW(RECEIVE_MESSAGE_FORMAT);
			}
			tmpStr.Format(tmpFor, userName, p->GetTime(), p->GetContent());
			allMsg = allMsg + tmpStr;
			next = p->GetNextMsg();
			p = next;
		}
	}

	return CString(allMsg);
}

CString EUser::GetMsgRecd()
{
	CString msgRecd;
	if (0 == msgNum || NULL == pMsg)
	{
		msgRecd = L"";
	}
	else {
		msgRecd = L"";
		EMessage* p = pMsg;
		EMessage* next = NULL;
		CString tmpFor, tmpStr;
		tmpFor.LoadStringW(SAVE_RECD);
		for (UINT i = 1; i <= msgNum && p != NULL; i++)
		{
			if (TRUE == p->GetSrMark()) {
				tmpStr.Format(tmpFor, p->GetTime(), L"SENT", p->GetContent());
			}
			else {
				tmpStr.Format(tmpFor, i, p->GetTime(), L"RECEIVED", p->GetContent());
			}
			
			msgRecd = msgRecd + tmpStr;
			next = p->GetNextMsg();
			p = next;
		}
	}

	return CString(msgRecd);
}

void EUser::insertMsg(EMessage  _pMsg)
{
	if (0 == msgNum)
	{
		EMessage* p = new EMessage(_pMsg.GetTime(), _pMsg.GetContent(),
			_pMsg.GetSrMark(), _pMsg.GetReadMark(), _pMsg.GetBurnMark());
		pMsg = p;
		endMsg = p;
	}
	else
	{
		endMsg->SetNextMsg(_pMsg);
		endMsg = endMsg->GetNextMsg();
	}
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

void EMessage::SetNextMsg(EMessage  _pMsg)
{
	EMessage* p = new EMessage(_pMsg.GetTime(), _pMsg.GetContent(),
		_pMsg.GetSrMark(), _pMsg.GetReadMark(), _pMsg.GetBurnMark());
	nextMsg = p;
}

void EMessage::ChangeRmk()
{
	readMark = TRUE;
}

EMessage::~EMessage()
{

}

EFileList::EFileList()
{
	listLen = 0;
	head = NULL;
	end = NULL;
}

UINT EFileList::GetListLen()
{
	return listLen;
}

EFile * EFileList::GetHead()
{
	return head;
}

void EFileList::InsertToList(EFile file)
{
	EFile* p = new EFile(file);
	if (0 == listLen){
		p->SetId(0);
		head = p;
		end = head;
		listLen++;
	}
	else {
		p->SetId(end->GetId() + 1);//make ID unique
		end->SetNextFile(p);
		end = end->GetNextFile();
		listLen++;
	}

}

void EFileList::DeleteFromList(CString path)
{
	EFile * p = head;
	EFile * tmp;
	if (listLen > 0 && p !=NULL) {
		for (; p != NULL;) {
			tmp = p;
			if (path == p->GetPath()) {
				tmp ->SetNextFile(p->GetNextFile());
				delete p;
				listLen--;
				break;
			}
		}
	}
}

EFileList::~EFileList()
{
}

EFile::EFile( CString _filePath, CString _title, double _p, BOOL _send)
{
	ID = 0;
	filePath = _filePath;
	fileTitle = _title;
	progress = _p;
	sendMrk = _send;
	next = NULL;
}

EFile::~EFile()
{
}

void EFile::SetProgress(double p)
{
	progress = p;
}

void EFile::SetNextFile(EFile* file)
{
	next = file;
}

void EFile::SetId(int id)
{
	ID = id;
}

int EFile::GetId()
{
	return ID;
}

CString EFile::GetIp()
{
	return CString(IP);
}

CString EFile::GetPath()
{
	return CString(filePath);
}

CString EFile::GetFileTitle()
{
	return CString(fileTitle);
}

double EFile::GetProgress()
{
	return progress;
}

EFile * EFile::GetNextFile()
{
	return next;
}
