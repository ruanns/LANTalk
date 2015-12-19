#include "stdafx.h"
#include "resource.h"

class EMessage {
public:
	EMessage(CString _t = L"", CString _m = L"Message", bool _sr = TRUE, bool _read = FALSE, bool _burn = FALSE);
	CString GetTime();
	CString GetContent();
	EMessage* GetNextMsg();
	BOOL GetSrMark();
	BOOL GetReadMark();
	BOOL GetBurnMark();
	void SetNextMsg(EMessage* _pMsg);
	void ChangeRmk();
	~EMessage();
private:
	CString time;
	CString content;
	EMessage* nextMsg;
	bool srMark;
	bool readMark;
	bool burnMark;
};


class EUser {
public:
	EUser(CString _name = L"UserName", CString _hostname = L"hostName", CString _ip = L"0.0.0.0", CString _mark = L"255.255.255.0"/*,UINT _group*/);
	void EditName(CString);
	CString GetHostName();
	CString GetName();
	CString GetIp();
	CString GetMark();
	EMessage* GetPmsg();
	UINT GetMsgNum();
	CString GetAllMessage();
	void insertMsg(EMessage* _pMsg);
	~EUser() {};
private:
	CString userName;
	CString hostName;
	CString ipAddress;
	CString Mark;
	UINT msgNum;
	EMessage* pMsg;
	EMessage* endMsg;
	//UINT group;
	//	bool clientMark;
};
class EUserList {
public:
	EUserList() {};
	~EUserList() {};
	
private:
	UINT number;
	EUser* Start;
	EUser* Next;
};



class EFileInfo {
public:
private:

};
