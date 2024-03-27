#pragma once
#include "CSendBuffer.h"
#include "CRecvBuffer.h"
#include "MyWindow.h"
#include "Job.h"
struct ChatReqLoginJob: public Job
{
	INT64	_accountNo;
	Array<WCHAR,20>	_id;			
	Array<WCHAR,20>	_nickName;	
	Array<char,64>	_sessionKey;
	void ProcessJob() override;
};
