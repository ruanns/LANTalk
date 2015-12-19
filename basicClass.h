#include "stdafx.h"


class EUser {
public:
	EUser(CString _name = L"UserName", CString _hostname = L"hostName", CString _ip = L"0.0.0.0", CString _mark = L"255.255.255.0"/*,UINT _group*/);
	void EditName(CString);
	CString GetHostName();
	CString GetName();
	CString GetIp();
	CString GetMark();
	~EUser() {};
private:
	CString userName;
	CString hostName;
	CString ipAddress;
	CString Mark;
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


class EMessage {
public:
	EMessage(CString, bool, bool, bool);
	void ChangeRmk();
	~EMessage();
private:
	UINT length;
	CString content;
	bool burnMark;
	bool srMark;
	bool readMark;
};
class EFileInfo {
public:
private:

};
