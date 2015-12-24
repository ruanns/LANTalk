#pragma once


#include "stdafx.h"
#include "resource.h"


class EMessage {
public:
	EMessage(CString _t = L"", CString _m = L"Message", bool _sr = TRUE, bool _read = FALSE, 
		bool _burn = FALSE);
	CString GetTime();
	CString GetContent();
	EMessage* GetNextMsg();
	BOOL GetSrMark();
	BOOL GetReadMark();
	BOOL GetBurnMark();
	void SetNextMsg(EMessage _pMsg);
	void ChangeRmk();
	~EMessage();
private:
	CString time;
	CString content;
	EMessage* nextMsg;
	bool srMark; //TRUE->SEND FAlSE->RECEIVED
	bool readMark;//TRUE->HAVE BEEN READ
	bool burnMark;//FALSE->NOT TO BURN
};

class EUser {
public:
	EUser(CString _name = L"UserName", CString _hostname = L"hostName", CString _ip = L"0.0.0.0", CString _mask = L"255.255.255.0"/*,UINT _group*/);
	void EditName(CString);
	CString GetHostName();
	CString GetName();
	CString GetIp();
	CString GetMask();
	EMessage* GetPmsg();
	UINT GetMsgNum();
	CString GetAllMessage();
	CString GetMsgRecd();
	void insertMsg(EMessage _pMsg);
	~EUser() {};
private:
	CString userName;
	CString hostName;
	CString ipAddress;
	CString Mask;
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

class EFile {
public:
	EFile(CString _filePath = L"", CString _name = L"", double _p = 0, BOOL _send = TRUE);
	~EFile();
	void SetProgress(double p);
	void SetNextFile(EFile* file);
	void SetId(int id);
	int GetId();
	CString GetIp();
	CString GetPath();
	CString GetFileName();
	double GetProgress();
	EFile* GetNextFile();
private:
	int ID;//unique id number
	CString IP;
	CString filePath;//full path
	CString fileName;
	double progress;
	BOOL sendMrk;//TRUE-> SEND; FALSE->RECEIVE;
	EFile * next;
};

class EFileList {
public:
	EFileList();
	UINT GetListLen();
	EFile * GetHead();
	void InsertToList(EFile file);
	void DeleteFromList(CString path);
	~EFileList();
private:
	UINT listLen;
	EFile* head;
	EFile* end;
};


struct FileInfo
{
int ID;
CString file;
int iAccept;
};